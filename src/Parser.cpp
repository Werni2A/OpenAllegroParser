#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <libzippp.h>

#include "DataStream.hpp"
#include "Drillmethod.hpp"
#include "General.hpp"
#include "HoleType.hpp"
#include "LayerStuff.hpp"
#include "PadstackUsage.hpp"
#include "Parser.hpp"


namespace fs = std::filesystem;


Parser::Parser(const fs::path& aFile)
{
    mFileType = getFileTypeByExtension(aFile);

    openFile(aFile);

    // @todo parse the version somehow
    mFileFormatVersion = FileFormatVersion::Unknown;
}


Parser::~Parser()
{
    closeFile();
}


FileType Parser::getFileTypeByExtension(const fs::path& aFile) const
{
    std::string extension = aFile.extension().string();

    // Ignore case of extension.
    std::transform(extension.begin(), extension.end(), extension.begin(),
            [](unsigned char c) { return std::tolower(c); }
        );

    FileType fileType;

    if(extension == ".brd")
    {
        fileType = FileType::brd;
    }
    else if(extension == ".mdd")
    {
        fileType = FileType::mdd;
    }
    else if(extension == ".dra")
    {
        fileType = FileType::dra;
    }
    else if(extension == ".psm")
    {
        fileType = FileType::psm;
    }
    else if(extension == ".ssm")
    {
        fileType = FileType::ssm;
    }
    else if(extension == ".fsm")
    {
        fileType = FileType::fsm;
    }
    else if(extension == ".osm")
    {
        fileType = FileType::osm;
    }
    else if(extension == ".bsm")
    {
        fileType = FileType::bsm;
    }
    else if(extension == ".pad")
    {
        fileType = FileType::pad;
    }
    else
    {
        throw std::runtime_error("Unknown file extension: " + extension);
    }

    return fileType;
}


std::vector<std::pair<std::string, size_t>> Parser::getFilesInBinary()
{
    std::vector<std::pair<std::string, size_t>> files;

    // Start at beginning of file.
    const size_t oldOffset = mDs.setCurrentOffset(0u);

    while(!mDs.isEoF())
    {
        const bool foundZip = gotoNextZip();

        if(foundZip)
        {
            const std::string fileName = fs::path{mInputFile}.replace_extension("zip").filename().string();
            files.push_back(std::make_pair(fileName, mDs.getCurrentOffset()));

            mDs.discardBytes(1u);

            // @todo Quit after fist ZIP was found as we don't handle multiple ZIPs in the binary
            //       very well. (The magic bytes of a ZIP appear a few times in the same ZIP,
            //       therefore it looks like there are a few ZIPs in the binary, though its only one).
            //       It might be a reasonable assumption, that there is only one ZIP contained in the binary.
            break;
        }
    }

    // Restore old offset.
    mDs.setCurrentOffset(oldOffset);

    return files;
}


void Parser::exportZipFiles(const fs::path& aOutputPath)
{
    const auto& files = getFilesInBinary();

    for(const auto& file : files)
    {
        const std::string& fileName   = file.first;
        const size_t&      fileOffset = file.second;

        if(fs::path(fileName).extension().string() == ".zip")
        {
            const size_t oldOffset = mDs.setCurrentOffset(fileOffset);

            exportZip(aOutputPath);

            mDs.setCurrentOffset(oldOffset);
        }
    }
}


void Parser::openFile(const fs::path& aFile)
{
    std::cout << "Opening file: " << aFile << std::endl;

    mDs = DataStream{aFile};

    if(!mDs)
    {
        throw std::runtime_error("Could not open file: " + aFile.string());
    }

    mInputFile     = aFile;
    mInputFileSize = fs::file_size(aFile);

    std::cout << "File contains " << mInputFileSize << " byte." << std::endl;
}


void Parser::closeFile()
{
    std::cout << "Closing file: " << mInputFile << std::endl;

    mDs.close();

    mInputFile.clear();
    mInputFileSize = 0u;
}


bool Parser::gotoNextZip()
{
    while(!mDs.isEoF())
    {
        // @todo The magic number appreas for each file in the ZIP. This leads to parsing the ZIP a few times right from
        //       the middle of the file, which fails. How can we differentiate the "real" start of the ZIP?
        const std::vector<uint8_t> magicNumberZip{0x50, 0x4b, 0x03, 0x04};
        if(magicNumberZip == mDs.peek(magicNumberZip.size())) // Compare with ZIP magic number
        {
            // Found ZIP.
            return true;
        }

        mDs.readUint8();
    }

    return false;
}


void Parser::exportZip(const fs::path& aOutputPath, size_t aComprZipSize)
{
    const size_t zipBufferLen = (aComprZipSize == 0u) ? (mInputFileSize - mDs.getCurrentOffset()) : aComprZipSize;
    std::unique_ptr<char[]> zipBuffer = std::make_unique<char[]>(zipBufferLen);

    mDs.read(zipBuffer.get(), zipBufferLen);

    // @todo Implement check for magic bytes
    // const std::vector<uint8_t> magicNumberZip{0x50, 0x4b, 0x03, 0x04};

    libzippp::ZipArchive& zf = *(libzippp::ZipArchive::fromBuffer(zipBuffer.get(), zipBufferLen));

    zf.open(libzippp::ZipArchive::ReadOnly);

    // Export ZIP container itself.
    {
        fs::path fileName = fs::path{mInputFile}.replace_extension("zip").filename();

        // If ZIP container consists only of 1 file, use that name instead.
        if(zf.getEntriesCount() == 1u)
        {
            const auto& entry = zf.getEntries().front();

            if(entry.isFile())
            {
                fileName = fs::path{entry.getName()}.replace_extension("zip").filename();
            }
        }

        fs::path filePath = aOutputPath / mInputFile.filename() / fileName;
        fs::create_directories(filePath.parent_path());

        std::cout << "Extract ZIP file: " << filePath.string() << std::endl;

        // Note: In case the ZIP size is not specified we use a buffer that is greater or equal the ZIP size.
        // Writing data after the end of the ZIP is not great but does no harm. The ZIP can still be opened correctly.

        std::ofstream ofs;
        ofs.open(filePath, std::ofstream::out | std::ofstream::binary);
        ofs.write(zipBuffer.get(), zipBufferLen);
        ofs.close();
    }

    // Export content of ZIP container.
    for(const auto& entry : zf.getEntries())
    {
        fs::path basePath = aOutputPath / mInputFile.filename();

        const fs::path entryPath = entry.getName();

        fs::create_directories((basePath / entryPath).parent_path());

        if(entry.isFile())
        {
            const libzippp_uint64 fileSize = entry.getSize();

            const void* binaryData = entry.readAsBinary();

            if(nullptr == binaryData)
            {
                throw std::runtime_error("Could not read ZIP as binary!");
            }

            fs::path filePath = basePath / entryPath;

            std::cout << "Extract from ZIP, " << fileSize << " Byte file: " << filePath.string() << std::endl;

            // Note: In case the ZIP size is not specified we use a buffer that is greater or equal the ZIP size.
            // Writing data after the end of the ZIP is not great but does no harm. The ZIP can still be opened correctly.

            // Write content of ZIP container.
            std::ofstream ofs;
            ofs.open(filePath, std::ofstream::out | std::ofstream::binary);
            ofs.write(static_cast<const char*>(binaryData), fileSize);
            ofs.close();

            // @todo figure out how to delete this. See documentation of the function that sets binaryData.
            delete static_cast<const uint8_t*>(binaryData);
            binaryData = nullptr;
        }
    }

    zf.close();
}


Pad Parser::readPad(size_t aIdx, bool aIsUsrLayer, const PadFile& aPadFile, const unknownParam& uparam)
{
    Type  type;
    Layer layer;

    const std::vector<padTypeLayer>& layerLst = (uparam.unknownFlag2 ? layerLst2 : layerLst1);

    if(!aIsUsrLayer)
    {
        type  = layerLst.at(aIdx).type;
        layer = layerLst.at(aIdx).layer;
    }
    else
    {
        type  = Type::USER_MASK;
        layer = Layer::USR_STR;
    }

    Pad pad{type, layer};

    if(aIsUsrLayer)
    {
        pad.mUsrStr = ""; // @todo set real value. Pass it somehow to this method
                          //       At the moment it is set outside of this function
                          //       in the returned Pad object
    }

    pad.setFigure(mDs.readUint16());
    pad.setSpecialCorners(mDs.readUint16());

    pad.setNsides(mDs.readUint32());

    pad.setWidth(mDs.readInt32());
    pad.setHeight(mDs.readInt32());

    pad.setCorner(mDs.readInt32());

    pad.setOffsetX(mDs.readInt32());
    pad.setOffsetY(mDs.readInt32());

    mDs.printUnknownData(std::cout, 4, "pad data - 0");

    pad.mIdxShapeSymolNameStr = mDs.readUint32();

    if(pad.mIdxShapeSymolNameStr == 0)
    {
        pad.mShapeSymbolNameStr == "";
    }
    else
    {
        pad.mShapeSymbolNameStr = aPadFile.getStrLstEntryByIdx(pad.mIdxShapeSymolNameStr);
    }

    return pad;
}


PadFile Parser::readPadFile(unknownParam uparam)
{
    PadFile padFile;

    // Specifies how many seconds are allowed to pass
    // until two contiguous sections are generated.
    const double maxTimeDiff = 2.0;

    mDs.assumeData({0x00, 0x05, 0x14, 0x00, 0x03, 0x00, 0x00, 0x00}, "Start Sequence - 0");
    // mDs.printUnknownData(std::cout, 8, "unknown - 0");

    mDs.assumeData({0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00}, "Start Sequence - 1");

    mDs.assumeData({0x03, 0x00, 0x00, 0x00}, "Start Sequence - 2");

    mDs.printUnknownData(std::cout, 32, "unknown - 1");

    // @todo This relates maybe to the standard layers in the padstack as we
    // have 25 of them and 1 of them is just rubbish, and can be ignored
    // => We have 24 standard packstack layers
    for(size_t i = 0u; i < 24u; ++i)
    {
        const uint32_t some_idx = mDs.readUint32();
        const uint32_t some_val = mDs.readUint32();

        std::cout << "some_idx = " << some_idx << "; some_val = " << some_val << std::endl;
    }

    // @todo probably always number 1 and represents idx = 1?
    // mDs.printUnknownData(std::cout, 4, "unkown - 2");
    mDs.assumeData({0x01, 0x00, 0x00, 0x00}, "unknown - 2");

    padFile.swVersion = mDs.readStrZeroTermBlock(60u);

    mDs.printUnknownData(std::cout, 58, "unknown - 3");

    padFile.accuracy = mDs.readUint16();

    // @todo What are those factors used for? Only for calculating angle = val / factor?
    const int32_t factor0 = mDs.readInt32(); // = -10,000 * 10^accuracy
    const int32_t factor1 = mDs.readInt32(); // = -10,000 * 10^accuracy
    const int32_t factor2 = mDs.readInt32(); // =  10,000 * 10^accuracy
    const int32_t factor3 = mDs.readInt32(); // =  10,000 * 10^accuracy

    // Sanity checks
    int32_t factor = 10000 * static_cast<int>(std::pow(10, padFile.accuracy));

    if(factor0 != -factor)
    {
        throw std::runtime_error("Unexpected: factor0 != " + std::to_string(-factor));
    }

    if(factor0 != factor1)
    {
        throw std::runtime_error("Unexpected: factor0 != factor1");
    }

    if(factor2 != factor)
    {
        throw std::runtime_error("Unexpected: factor2 != " + std::to_string(factor));
    }

    if(factor2 != factor3)
    {
        throw std::runtime_error("Unexpected: factor2 != factor3");
    }

    padFile.unit = ToUnits(mDs.readUint16());

    // @todo somehow related to user defined layers with symbol/flash
    mDs.printUnknownData(std::cout, 227, "unknown - 4");

    const uint16_t additionalStr = mDs.readUint16();

    mDs.printUnknownData(std::cout, 8, "unknown - 5");

    mDs.assumeZero(449, "unknown - 6");

    mDs.printUnknownData(std::cout, 36, "unknown - 7");

    for(size_t i = 0u; i < 20u; ++i)
    {
        const uint32_t sth0 = mDs.readUint32();
        const uint32_t sth1 = mDs.readUint32();

        std::cout << "sth0 = " << sth0 << "; sth1 = " << sth1 << std::endl;
    }

    mDs.printUnknownData(std::cout, 20, "unknown - 8");

    mDs.assumeZero(248, "unknown - 9");

    const std::array<std::string, 6> predefStrLst = {
        "BEGIN LAYER",
        "END LAYER",
        "AIR",
        "COPPER",
        "FR-4",
        "PRIMARY"
    };

    for(size_t i = 0u; i < 7u + additionalStr + uparam.additionalStr2; ++i)
    {
        const uint32_t    idx = mDs.readUint32();
        const std::string str = mDs.readStrZeroTerm4BytePad();

        padFile.idxStrPairLst.push_back(std::make_pair(idx, str));

        std::cout << "idxStrPairLst[" << std::to_string(padFile.idxStrPairLst.size()) << "] : "
                  << "idx = " << idx << "; str = " << str << std::endl;
    }

    // Sanity check
    for(size_t i = 0u; i < predefStrLst.size(); ++i)
    {
        expectStr(padFile.idxStrPairLst.at(i).second, predefStrLst[i]);
    }

    // @todo Still unknown whether there is a string stored or just some
    //       other info
    {
        const uint32_t idx    = mDs.readUint32();

        mDs.printUnknownData(std::cout, 4, "unknown - 10");

        const std::string str = "";

        padFile.idxStrPairLst.push_back(std::make_pair(idx, str));

        std::cout << "idxStrPairLst[" << std::to_string(padFile.idxStrPairLst.size()) << "] : "
                  << "idx = " << idx << "; str = " << str << std::endl;
    }

    // drillinfo

    // Contains drilltoolsize
    {
        const uint32_t idx    = mDs.readUint32();
        const std::string str = mDs.readStrZeroTerm4BytePad();

        padFile.idxStrPairLst.push_back(std::make_pair(idx, str));

        std::cout << "idxStrPairLst[" << std::to_string(padFile.idxStrPairLst.size()) << "] : "
                  << "idx = " << idx << "; str = " << str << std::endl;
    }

    // @todo Maybe Add the above two indicies and strings to the loop and increase the
    // limit from 7 to 9

    // @todo figure out, when it is set. It think it is somehow related to
    //       drills, backdrills or multiple drill rows/columns
    if(uparam.unknownFlag)
    {
        mDs.printUnknownData(std::cout, 8, "unknown - 11");
    }

    mDs.printUnknownData(std::cout, 4, "unknown - 12");

    padFile.strIdxPadName       = mDs.readUint32();
    padFile.idxUnknown          = mDs.readUint32();
    padFile.strIdxDrillToolSize = mDs.readUint32(); // Is 0 when no DrillToolSize is specified (empty string)

    // mDs.printUnknownData(std::cout, 4, "unknown - 13");
    mDs.assumeZero(4, "unknown - 13");

    // @todo padstackusage is probably a bit field where the first two
    //       bits are something different. See PadstackUsage.hpp for more info.
    const uint8_t tmpPadstackusage = mDs.readUint8();

    if(tmpPadstackusage & 0x03 != 0x02)
    {
        throw std::runtime_error("New bit field value found in tmpPadstackusage");
    }

    padFile.padstackusage = ToPadstackUsage(tmpPadstackusage);

    padFile.drillmethod = ToDrillmethod(mDs.readUint8());

    // Bit 0 - 2 = Drill Hole Type
    // Bit     3 = @todo Unknown flag
    // Bit     4 = Staggered Drills
    // Bit     5 = Plated Drill Holes
    const uint8_t bit_field = mDs.readUint8();

    padFile.holeType        = ToHoleType(bit_field & 0x07);
    const bool unknown_flag = static_cast<bool>(bit_field & 0x08);
    std::cout << "unknown_flag = " << std::to_string(unknown_flag) << std::endl;
    padFile.staggeredDrills = static_cast<bool>(bit_field & 0x10);
    padFile.plated          = static_cast<bool>(bit_field & 0x20);

    // Check for unknown bits that are set
    if(bit_field & ~0x3f)
    {
        throw std::runtime_error("Unknown bit in bit_field set! 0x" + ToHex(bit_field, 2));
    }

    // @todo it's either 0x0100 or 0x0500
    //       Somehow related to numUserLayers as its always 5 when
    //       numUserLayers > 0. Maybe just a flag to indicate when user layers
    //       are present?
    uint16_t foo = mDs.readUint16();

    if(foo != 0x0100 && foo != 0x0500)
    {
        throw std::runtime_error("New value found! 0x" + ToHex(foo, 2));
    }

    // Bit 0 = Not suppress not connected internal pads
    // Bit 1 = Poly Via
    const uint8_t bit_field2 = mDs.readUint8();

    padFile.not_suppress_nc_internal_pads = static_cast<bool>(bit_field2 & 0x01);
    padFile.isPolyVia                     = static_cast<bool>(bit_field2 & 0x02);

    // Check for unknown bits that are set
    if(bit_field2 & ~0x03)
    {
        throw std::runtime_error("Unknown bit in bit_field2 set! 0x" + ToHex(bit_field2, 2));
    }

    mDs.printUnknownData(std::cout, 8, "unknown - 15");

    // multidrill

    padFile.drill_rows    = mDs.readUint16();
    padFile.drill_columns = mDs.readUint16();

    const uint8_t lock_layer_span = mDs.readUint8();
    padFile.lock_layer_span = static_cast<bool>(lock_layer_span);

    if(lock_layer_span > 1)
    {
        throw std::runtime_error("Epected boolean value! 0x" + ToHex(lock_layer_span, 2));
    }

    mDs.assumeZero(1, "unknown - 16");
    // mDs.printUnknownData(std::cout, 1, "unknown - 16");

    padFile.offsetX = mDs.readInt32();
    padFile.offsetY = mDs.readInt32();

    padFile.clearance_columns = mDs.readUint32();
    padFile.clearance_rows    = mDs.readUint32();

    padFile.finished_size     = mDs.readInt32();

    // For holeType == (OVAL_SLOT || RECT_SLOT) this is
    // the tolerance on x-axis.
    padFile.positivetolerance = mDs.readInt32();
    padFile.negativetolerance = mDs.readInt32();

    // The values should always be zero when
    // holeType != (OVAL_SLOT || RECT_SLOT)
    padFile.slothole_width  = mDs.readUint32();
    padFile.slothole_height = mDs.readUint32();
    padFile.slothole_positivetolerancey = mDs.readInt32();
    padFile.slothole_negativetolerancey = mDs.readInt32();

    padFile.width  = mDs.readUint32();
    padFile.height = mDs.readUint32();

    padFile.figure = ToFigure(mDs.readUint32());

    padFile.characters = mDs.readStrZeroTerm4BytePad();

    // backdrill

    padFile.diameter = mDs.readUint32();

    // mDs.printUnknownData(std::cout, 12, "unknown - 19");
    mDs.assumeZero(8, "unknown - 19");

    padFile.back_drill_figure_width  = mDs.readUint32();
    padFile.back_drill_figure_height = mDs.readUint32();

    padFile.back_drill_figure = ToFigure(mDs.readUint32());

    padFile.back_drill_characters = mDs.readStrZeroTerm4BytePad();

    // counterboresink

    padFile.counter_drill_diameter = mDs.readInt32();
    padFile.counter_drill_positivetolerance = mDs.readInt32();
    padFile.counter_drill_negativetolerance = mDs.readInt32();

    padFile.counterangle = mDs.readInt32();
    // @todo maybe the scaling factor 1/10000 depends on the factors defined at the beginning of the method
    //       10,000 * 10^accuracy?
    // std::cout << "counterangle = " << std::to_string(padFile.counterangle / 10000u) << std::endl;

    mDs.printUnknownData(std::cout, 8, "Something with counterdepth");

    mDs.assumeZero(32, "unknown - 20");
    // mDs.printUnknownData(std::cout, 32, "unknown - 20");


    size_t beginLayers = 0u;

    if(uparam.unknownFlag2)
    {
        beginLayers = 4u;
    }

    for(size_t i = 0u; i < 25u + beginLayers; ++i)
    {
        padFile.preDefLayers.push_back(readPad(i, false, padFile, uparam));

    }

    for(size_t i = 0u; i < uparam.numUserLayers; ++i)
    {
        const uint32_t idxLayerName = mDs.readUint32();

        Pad pad = readPad(i, true, padFile, uparam);

        pad.mUsrStr = padFile.getStrLstEntryByIdx(idxLayerName);

        padFile.usrDefLayers.push_back(pad);
    }

    mDs.printUnknownData(std::cout, 56, "unknown - 21");

    padFile.dateTime1 = ToTime(mDs.readUint32());

    mDs.printUnknownData(std::cout, 18, "unknown - 22");

    // @todo not sure about this one
    const size_t usernameLen = mDs.readUint32();

    mDs.printUnknownData(std::cout, 2, "unknown - 23");

    padFile.username = mDs.readStrZeroTerm4BytePad();

    if(padFile.username.size() + 1 != usernameLen) // +1 for terminating zero byte.
    {
        throw std::runtime_error("Expected different text length!");
    }

    mDs.printUnknownData(std::cout, 32, "unknown - 24");

    const size_t someTxtLen = mDs.readUint32();

    const std::string quickViewText = mDs.readStrZeroTermBlock(128);

    expectStr(quickViewText, "_QuickViewText");

    const std::string quickViewsRef = "_QUICKVIEWS";
    std::string quickViews = mDs.readStrZeroTermBlock(32);

    expectStr(quickViews, quickViewsRef);

    const auto sanityCheckSectionTimeDiff = [] (time_t aStartTime, time_t aEndTime, double aMaxTimeDiff) -> void
        {
            // Sanity check that previous sections were created within maxSecDiff seconds.
            if(std::difftime(aEndTime, aStartTime) > aMaxTimeDiff)
            {
                throw std::runtime_error("Difference in generation time must be lower than "
                    + std::to_string(aMaxTimeDiff) + " seconds but date and time is start "
                    + DateTimeToStr(aStartTime) + " and end " + DateTimeToStr(aEndTime) + "!");
            }
        };

    padFile.dateTime2 = ToTime(mDs.readUint32());

    sanityCheckSectionTimeDiff(padFile.dateTime1, padFile.dateTime2, maxTimeDiff);

    mDs.assumeZero(8, "unknown - 23");

    const std::string someTxt = mDs.readStrZeroTerm4BytePad();

    if(someTxt.size() + 1 != someTxtLen) // +1 for terminating zero byte.
    {
        throw std::runtime_error("Expected different text length!");
    }

    // std::cout << "someTxt = " << someTxt << std::endl;

    mDs.printUnknownData(std::cout, 8, "unknown - 25");

    const std::string quickViewGraph = mDs.readStrZeroTermBlock(128);

    expectStr(quickViewGraph, "_QuickViewGraph");

    quickViews = mDs.readStrZeroTermBlock(32);

    expectStr(quickViews, quickViewsRef);

    padFile.dateTime3 = ToTime(mDs.readUint32());

    sanityCheckSectionTimeDiff(padFile.dateTime2, padFile.dateTime3, maxTimeDiff);

    mDs.printUnknownData(std::cout, 36, "unknown - 26");

    const uint32_t zipSize = mDs.readUint32();

    const std::string quickViewJson = mDs.readStrZeroTermBlock(128);

    expectStr(quickViewJson, "_QuickViewJson");

    quickViews = mDs.readStrZeroTermBlock(32);

    expectStr(quickViews, quickViewsRef);

    padFile.dateTime4 = ToTime(mDs.readUint32());

    sanityCheckSectionTimeDiff(padFile.dateTime3, padFile.dateTime4, maxTimeDiff);

    mDs.printUnknownData(std::cout, 8, "unknown - 27");

    exportZip(fs::temp_directory_path() / "OpenAllegroParser", zipSize);

    mDs.padTo4ByteBoundary();

    mDs.printUnknownData(std::cout, 8, "unknown - 28");

    const std::string newDbFeatures = mDs.readStrZeroTermBlock(160);

    expectStr(newDbFeatures, "NEW_DB_FEATURES");

    padFile.dateTime5 = ToTime(mDs.readUint32());

    sanityCheckSectionTimeDiff(padFile.dateTime4, padFile.dateTime5, maxTimeDiff);

    mDs.assumeZero(12, "unknown - 28.5");

    mDs.printUnknownData(std::cout, 8, "unknown - 29");

    const std::string allegroDesignWasLastSaved = mDs.readStrZeroTermBlock(160);

    expectStr(allegroDesignWasLastSaved, "ALLEGRO_DESIGN_WAS_LAST_SAVED");

    padFile.dateTime6 = ToTime(mDs.readUint32());

    sanityCheckSectionTimeDiff(padFile.dateTime5, padFile.dateTime6, maxTimeDiff);

    mDs.assumeZero(8, "unknown - 30");

    padFile.programAndVersion = mDs.readStrZeroTerm4BytePad();

    if(!mDs.isEoF())
    {
        throw std::runtime_error("Expected EoF!");
    }

    return padFile;
}
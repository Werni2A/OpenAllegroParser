#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <fmt/core.h>
#include <libzippp.h>
#include <spdlog/spdlog.h>

#include "../include/DataStream.hpp"
#include "../include/Drillmethod.hpp"
#include "../include/General.hpp"
#include "../include/HoleType.hpp"
#include "../include/LayerStuff.hpp"
#include "../include/PadstackUsage.hpp"
#include "../include/Parser.hpp"


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

    // Ignore case of extension
    extension = to_lower(extension);

    const std::map<std::string, FileType> extensionFileTypeMap =
        {
            {".brd", FileType::brd},
            {".mdd", FileType::mdd},
            {".dra", FileType::dra},
            {".psm", FileType::psm},
            {".ssm", FileType::ssm},
            {".fsm", FileType::fsm},
            {".osm", FileType::osm},
            {".bsm", FileType::bsm},
            {".pad", FileType::pad},
        };

    FileType fileType;

    try
    {
        fileType = extensionFileTypeMap.at(extension);
    }
    catch(...)
    {
        throw std::runtime_error("Unknown file extension `" + extension + "`");
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


Pad Parser::readPad(size_t aIdx, bool aIsUsrLayer, const PadFile& aPadFile)
{
    Type  type;
    Layer layer;

    const std::vector<PadTypeLayer>& layerLst = (uparam.bool2 ? layerLst2 : layerLst1);

    if(!aIsUsrLayer)
    {
        type  = layerLst.at(aIdx).type;
        layer = layerLst.at(aIdx).layer;
    }
    else
    {
        type  = Type::USER_MASK;
        layer = Layer::USER_STR;
    }

    Pad pad{type, layer};

    if(aIsUsrLayer)
    {
        pad.mUsrStr = ""; // @todo set real value. Pass it somehow to this method
                          //       At the moment it is set outside of this function
                          //       in the returned Pad object
    }

    if(aIsUsrLayer)
    {
        pad.mIdxUsrLayerName = mDs.readUint32();
    }

    if(pad.mIdxUsrLayerName)
    {
        pad.mUsrStr = aPadFile.getStrLstEntryByIdx(pad.mIdxUsrLayerName.value());
    }
    else
    {
        pad.mUsrStr = "";
    }

    pad.setFigure(mDs.readUint16());

    pad.setSpecialCorners(mDs.readUint16());

    pad.setNsides(mDs.readUint32());

    pad.setWidth(mDs.readInt32());
    pad.setHeight(mDs.readInt32());

    pad.setCorner(mDs.readInt32());

    pad.setOffsetX(mDs.readInt32());
    pad.setOffsetY(mDs.readInt32());

    pad.mIdxFlashStr = mDs.readUint32();

    if(pad.mIdxFlashStr == 0)
    {
        pad.mFlashStr == "";
    }
    else
    {
        pad.mFlashStr = aPadFile.getStrLstEntryByIdx(pad.mIdxFlashStr);
    }

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


Symbol Parser::readSymbol()
{
    Symbol obj;

    obj.width  = mDs.readUint32();
    obj.height = mDs.readUint32();

    obj.figure = ToFigure(mDs.readUint32());

    obj.characters = mDs.readStrZeroTerm4BytePad();

    return obj;
}


PadFile Parser::readPadFile(unknownParam uparam)
{
    this->uparam = uparam;

    PadFile padFile;

    // Specifies how many seconds are allowed to pass
    // until two contiguous sections are generated.
    const double maxTimeDiff = 2.0;

    mDs.assumeData({0x00, 0x05, 0x14, 0x00, 0x03, 0x00, 0x00, 0x00}, "Start Sequence - 0");
    // mDs.printUnknownData(8, "unknown - 0");

    mDs.assumeData({0x04, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00}, "Start Sequence - 1");

    mDs.assumeData({0x03, 0x00, 0x00, 0x00}, "Start Sequence - 2");

    const uint32_t someStringIndexSize = mDs.readUint32();
    std::cout << "someStringIndexSize = " << someStringIndexSize << std::endl;
    std::cout << "Expect " << someStringIndexSize - 13 << " user design layers";

    mDs.assumeData({0x0a, 0x0d, 0x0a, 0x00, 0x00, 0x00, 0x00, 0x02}, "unknown - 0.f");

    const uint32_t fileSize = mDs.readUint32();

    if(fileSize != mInputFileSize)
    {
        throw std::runtime_error{fmt::format("File size is {} but got {} Byte!", mInputFileSize, fileSize)};
    }

    const uint32_t probably_crc = mDs.readUint32();
    std::cout << fmt::format("probably_crc = {0:d} = {0:#b}", probably_crc) << std::endl;

    auto get_ones = [] (uint32_t aVal) -> uint32_t
        {
            uint32_t ctr = 0u;
            for(size_t i = 0u; i < 32u; ++i)
            {
                ctr += (aVal >> (31 - i)) & 0x01;
            }
            return ctr;
        };

    auto get_zeros = [] (uint32_t aVal) -> uint32_t
        {
            uint32_t ctr = 0u;
            for(size_t i = 0u; i < 32u; ++i)
            {
                ctr += (((aVal >> (31 - i)) & 0x01) + 1) % 2;
            }
            return ctr;
        };

    std::cout << " zeros = " << get_zeros(probably_crc) << "; ones = " << get_ones(probably_crc) << std::endl;
    const uint32_t some_val = mDs.readUint32();
    std::cout << "some_val = " << some_val << std::endl;

    if(some_val != 0x14 && some_val != 0x13)
    {
        throw std::runtime_error("Unexpected value for some_val, got " + std::to_string(some_val));
    }

    mDs.assumeZero(8, "unknown - 1");

    // mDs.printUnknownData(8, "unknown - 1");

    // @todo This relates maybe to the standard layers in the padstack as we
    // have 25 of them and 1 of them is just rubbish, and can be ignored
    // => We have 24 standard packstack layers
    for(size_t i = 0u; i < 24u; ++i)
    {
        const uint32_t some_idx = mDs.readUint32();
        const uint32_t some_val = mDs.readUint32();

        spdlog::info("[{:>2}]: some_idx = {:>2}; some_val = {:>3}", i, some_idx, some_val);
    }

    // @todo probably always number 1 and represents idx = 1?
    // mDs.printUnknownData(4, "unkown - 2");
    mDs.assumeData({0x01, 0x00, 0x00, 0x00}, "unknown - 2");

    padFile.swVersion = mDs.readStrZeroTermBlock(60u);

    // mDs.printUnknownData(58, "unknown - 3");
    mDs.assumeData({0x02}, "unknown - 3a");
    mDs.assumeZero(57, "unknown - 3b");

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
    mDs.printUnknownData(46, "unknown - 4");

    size_t userStrCtr = 0u;

    // A maximum of 32 user mask layers is allowed.
    // Try to insert more than 32 in the padstack_editor.exe and
    // observe the error message.
    std::vector<size_t> userLayerStrIdxLst;
    for(size_t i = 0u; i < 32u; ++i)
    {
        // Index represents first element in idxStrPairLst tuple
        // I.e. it represents the name of the user mask layer
        const uint32_t user_layer_idx = mDs.readUint32();
        userLayerStrIdxLst.push_back(user_layer_idx);

        if(user_layer_idx != 0u)
        {
            userStrCtr++;
        }

        spdlog::info("userLayerStrIdxLst[{:>2}]: {:>2} = {}", i, userStrCtr, user_layer_idx);
    }

    mDs.printUnknownData(53, "unknown - 4");

    // @todo Figure out which exact strings are counted
    const uint16_t additionalStr = mDs.readUint16();

    if(additionalStr != userStrCtr)
    {
        throw std::runtime_error(fmt::format("Expected additionalStr = {} is equal userStrCtr = {}!",
            additionalStr, userStrCtr));
    }

    mDs.assumeData({0x00, 0x01, 0x00, 0x00}, "unknown - 5a");

    mDs.printUnknownData(4, "unknown - 5");

    mDs.assumeZero(449, "unknown - 6");

    mDs.assumeData({0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, "unknown - 7a");
    mDs.assumeData({0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, "unknown - 7b");
    mDs.assumeData({0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, "unknown - 7c");
    mDs.assumeData({0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, "unknown - 7d");
    mDs.assumeData({0x09, 0x00, 0x00, 0x00}, "unknown - 7e");

    for(size_t i = 0u; i < 20u; ++i)
    {
        const uint32_t sth_first  = mDs.readUint32();
        const uint32_t sth_second = mDs.readUint32();

        spdlog::info("[{:>2}]: sth_first = {:>3}; sth_second = {:>3}", i, sth_first, sth_second);
    }

    mDs.assumeData({0x00, 0x00, 0x00, 0x00}, "unknown - 8.0");
    mDs.assumeData({0x0c, 0x00, 0x00, 0x00}, "unknown - 8.1");
    mDs.assumeData({0x00, 0x00, 0x00, 0x00}, "unknown - 8.2");
    mDs.assumeData({0x14, 0x00, 0x00, 0x00}, "unknown - 8.3");
    mDs.assumeData({0x00, 0x00, 0x00, 0x00}, "unknown - 8.4");

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

        spdlog::info("idxStrPairLst[{:>2}]: idx = {:>2}; str = {}", i, idx, str);
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

        spdlog::info("idxStrPairLst[{:>2}]: idx = {:>2}; str = {}", padFile.idxStrPairLst.size() - 1, idx, str);
    }

    // drillinfo

    // Contains drilltoolsize
    {
        const uint32_t idx    = mDs.readUint32();
        const std::string str = mDs.readStrZeroTerm4BytePad();

        padFile.idxStrPairLst.push_back(std::make_pair(idx, str));

        spdlog::info("idxStrPairLst[{:>2}]: idx = {:>2}; str = {}", padFile.idxStrPairLst.size() - 1, idx, str);
    }

    // @todo Maybe Add the above two indicies and strings to the loop and increase the
    // limit from 7 to 9

    // @todo figure out, when it is set. It think it is somehow related to
    //       drills, backdrills or multiple drill rows/columns
    if(uparam.bool1)
    {
        mDs.assumeData({0x1c, 0x00}, "unknown - 11.0");
        mDs.printUnknownData(6, "unknown - 11.5");
    }

    mDs.printUnknownData(4, "unknown - 12");
    // mDs.assumeData({0x07, 0x00, 0x00, 0x00}, "unknown - 12");

    padFile.strIdxPadName       = mDs.readUint32();
    padFile.idxUnknown          = mDs.readUint32();
    padFile.strIdxDrillToolSize = mDs.readUint32(); // Is 0 when no DrillToolSize is specified (empty string)

    // mDs.assumeZero(4, "unknown - 13");
    mDs.printUnknownData(4, "unknown - 13");

    // Bit 0: probUserDesignLayerPresent
    // Bit 1: Some unknown flag that is set when bit 0 is clear @todo
    // Bit 2 to 7: padstackusage
    const uint8_t tmp_bitfield = mDs.readUint8();


    const bool probUserDesignLayerPresent = static_cast<bool>(tmp_bitfield & 0x01); // @todo Check correctness
    const bool unknown_flag2              = static_cast<bool>(tmp_bitfield & 0x02); // @todo Figure out the meaning
    padFile.padstackusage = ToPadstackUsage((tmp_bitfield & 0xfc) >> 2);

    spdlog::info("unknown_flag2 = {}", unknown_flag2);

    if(probUserDesignLayerPresent && unknown_flag2)
    {
        throw std::runtime_error(fmt::format("Unexpected bit field value found in tmp_bitfield = {:#04x}", tmp_bitfield));
    }

    padFile.drillmethod = ToDrillmethod(mDs.readUint8());
    spdlog::debug("drillmethod = {}", to_string(padFile.drillmethod));

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
    //       Somehow related to userStrCtr as its always 5 when
    //       userStrCtr > 0. Maybe just a flag to indicate when user layers
    //       are present?
    const uint16_t foo = mDs.readUint16();

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

    // @todo This should be relatively easy to figure out as soon
    //       as we find a pad where this values are not equal to 0.
    // mDs.printUnknownData(6, "unknown - 15");
    mDs.assumeZero(6, "unknown - 15");

    // multidrill

    padFile.drill_rows    = mDs.readUint16();
    spdlog::debug("drill_rows    = {}", padFile.drill_rows);
    padFile.drill_columns = mDs.readUint16();
    spdlog::debug("drill_columns = {}", padFile.drill_columns);

    // @todo figure out why -2. Maybe it counts more than just the user design layers?
    //       E.g. additionally the Begin and End layer
    const uint16_t someVal77 = mDs.readUint16();
    const uint16_t numUserDesignLayers = (int)someVal77 - 2 < 0 ? 0 : someVal77 - 2;
    spdlog::critical("numUserDesignLayers = {}", numUserDesignLayers);

    const uint8_t lock_layer_span = mDs.readUint8();
    padFile.lock_layer_span = static_cast<bool>(lock_layer_span);

    if(lock_layer_span > 1)
    {
        throw std::runtime_error("Epected boolean value! 0x" + ToHex(lock_layer_span, 2));
    }

    mDs.assumeZero(1, "unknown - 16");
    // mDs.printUnknownData(1, "unknown - 16");

    padFile.offsetX = mDs.readInt32();
    spdlog::debug("offsetX = {}", padFile.offsetX);
    padFile.offsetY = mDs.readInt32();
    spdlog::debug("offsetY = {}", padFile.offsetY);

    padFile.clearance_columns = mDs.readUint32();
    spdlog::debug("clearance_columns = {}", padFile.clearance_columns);
    padFile.clearance_rows    = mDs.readUint32();
    spdlog::debug("clearance_rows = {}", padFile.clearance_rows);

    padFile.finished_size     = mDs.readInt32();
    spdlog::debug("finished_size = {}", padFile.finished_size);

    // For holeType == (OVAL_SLOT || RECT_SLOT) this is
    // the tolerance on x-axis. Otherwise for symmetric
    // holes this is the tolerance on x- and y-axis.
    padFile.positivetolerance = mDs.readInt32();
    spdlog::debug("positivetolerance = {}", padFile.positivetolerance);
    padFile.negativetolerance = mDs.readInt32();
    spdlog::debug("negativetolerance = {}", padFile.negativetolerance);

    // The values should always be zero when
    // holeType != (OVAL_SLOT || RECT_SLOT)
    padFile.slothole_width  = mDs.readUint32();
    spdlog::debug("slothole_width = {}", padFile.slothole_width);
    padFile.slothole_height = mDs.readUint32();
    spdlog::debug("slothole_height = {}", padFile.slothole_height);
    padFile.slothole_positivetolerancey = mDs.readInt32();
    spdlog::debug("slothole_positivetolerancey = {}", padFile.slothole_positivetolerancey);
    padFile.slothole_negativetolerancey = mDs.readInt32();
    spdlog::debug("slothole_negativetolerancey = {}", padFile.slothole_negativetolerancey);

    padFile.drillSymbol = readSymbol();
    spdlog::debug("drillSymbol = {}", to_string(padFile.drillSymbol));

    // backdrill

    padFile.diameter = mDs.readUint32();
    spdlog::debug("diameter = {}", padFile.diameter);

    // mDs.printUnknownData(12, "unknown - 19");
    mDs.assumeZero(8, "unknown - 19");

    padFile.backDrillSymbol = readSymbol();
    spdlog::debug("backDrillSymbol = {}", to_string(padFile.backDrillSymbol));

    // counterboresink

    padFile.counter_drill_diameter = mDs.readInt32();
    spdlog::debug("counter_drill_diameter = {}", padFile.counter_drill_diameter);
    padFile.counter_drill_positivetolerance = mDs.readInt32();
    spdlog::debug("counter_drill_positivetolerance = {}", padFile.counter_drill_positivetolerance);
    padFile.counter_drill_negativetolerance = mDs.readInt32();
    spdlog::debug("counter_drill_negativetolerance = {}", padFile.counter_drill_negativetolerance);

    padFile.counterangle = mDs.readInt32();
    // @todo maybe the scaling factor 1/10000 depends on the factors defined at the beginning of the method
    //       10,000 * 10^accuracy?
    spdlog::warn("counterangle = {}", padFile.counterangle / 10000u);
    spdlog::debug("counterangle = {}", padFile.counterangle);

    mDs.printUnknownData(8, "Something with counterdepth");

    mDs.assumeZero(32, "unknown - 20");
    // mDs.printUnknownData(32, "unknown - 20");

    const std::vector<PadTypeLayer>& layerLst = (uparam.bool2 ? layerLst2 : layerLst1);

    for(size_t i = 0u; i < layerLst.size(); ++i)
    {
        const Pad pad = readPad(i, false, padFile);

        padFile.preDefLayers.push_back(pad);
    }

    // @todo probably rename userStrCtr
    for(size_t i = 0u; i < userStrCtr; ++i)
    {
        const Pad pad = readPad(i, true, padFile);

        padFile.usrDefLayers.push_back(pad);
    }

    mDs.printUnknownData(std::cout, 56, "unknown - 21");

    padFile.dateTime1 = ToTime(mDs.readUint32());

    mDs.printUnknownData(2, "unknown - 22a");

    mDs.assumeData({0xdc, 0x02}, "unknown - 22.b");

    mDs.printUnknownData(2, "unknown - 22c");

    mDs.printUnknownData(10, "unknown - 22d");

    mDs.assumeData({0x68, 0x00}, "unknown - 22.f");

    // @todo not sure about this one. Looks like the name becomes truncated
    const size_t usernameLen = mDs.readUint32();

    // mDs.printUnknownData(2, "unknown - 23");
    mDs.assumeData({0x00, 0x00}, "unknown - 23");

    padFile.username = mDs.readStrZeroTerm4BytePad();

    if(padFile.username.size() + 1 != usernameLen) // +1 for terminating zero byte.
    {
        throw std::runtime_error("Expected different username text length!");
    }

    mDs.printUnknownData(28, "unknown - 24");

    const std::vector<uint8_t> unknown_identifier = {0x3b, 0x00, 0x00, 0x00};
    mDs.assumeData(unknown_identifier, "unknown - 24.a");

    const size_t specificationLen = mDs.readUint32();

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

    padFile.specification = mDs.readStrZeroTerm4BytePad();

    if(padFile.specification.size() + 1 != specificationLen) // +1 for terminating zero byte.
    {
        throw std::runtime_error("Expected different specification text length!");
    }

    mDs.assumeData(unknown_identifier, "unknown - 24.f");

    mDs.printUnknownData(4, "unknown - 25");

    const std::string quickViewGraph = mDs.readStrZeroTermBlock(128);

    expectStr(quickViewGraph, "_QuickViewGraph");

    quickViews = mDs.readStrZeroTermBlock(32);

    expectStr(quickViews, quickViewsRef);

    padFile.dateTime3 = ToTime(mDs.readUint32());

    sanityCheckSectionTimeDiff(padFile.dateTime2, padFile.dateTime3, maxTimeDiff);

    mDs.assumeData({0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00}, "unknown - 25.a");
    mDs.assumeData({0x01, 0x00, 0x09, 0x00, 0x00, 0x03, 0x0c, 0x00}, "unknown - 25.b");
    mDs.assumeData({0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00}, "unknown - 25.c");
    mDs.assumeData({0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00}, "unknown - 25.d");

    mDs.assumeData(unknown_identifier, "unknown - 25.e");

    const size_t zipSize = mDs.readUint32();

    const std::string quickViewJson = mDs.readStrZeroTermBlock(128);

    expectStr(quickViewJson, "_QuickViewJson");

    quickViews = mDs.readStrZeroTermBlock(32);

    expectStr(quickViews, quickViewsRef);

    padFile.dateTime4 = ToTime(mDs.readUint32());

    sanityCheckSectionTimeDiff(padFile.dateTime3, padFile.dateTime4, maxTimeDiff);

    mDs.printUnknownData(8, "unknown - 27");

    exportZip(fs::temp_directory_path() / "OpenAllegroParser", zipSize);

    mDs.padTo4ByteBoundary();

    const std::vector<uint8_t> unknown_identifier2 = {0x3b, 0x00, 0x01, 0x00};
    mDs.assumeData(unknown_identifier2, "unknown - 27.1");

    mDs.printUnknownData(4, "unknown - 28");

    const std::string newDbFeatures = mDs.readStrZeroTermBlock(160);

    expectStr(newDbFeatures, "NEW_DB_FEATURES");

    padFile.dateTime5 = ToTime(mDs.readUint32());

    sanityCheckSectionTimeDiff(padFile.dateTime4, padFile.dateTime5, maxTimeDiff);

    mDs.assumeZero(12, "unknown - 28.5");

    mDs.assumeData(unknown_identifier2, "unknown - 28.6");

    mDs.printUnknownData(4, "unknown - 29");

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
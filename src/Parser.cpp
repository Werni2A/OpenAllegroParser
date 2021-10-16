#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <libzippp.h>

#include "DataStream.hpp"
#include "General.hpp"
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
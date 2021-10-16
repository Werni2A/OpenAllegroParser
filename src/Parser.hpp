#ifndef PARSER_H
#define PARSER_H


#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "DataStream.hpp"
#include "General.hpp"


namespace fs = std::filesystem;


class Parser
{
public:

    Parser(const fs::path& aFile);

    ~Parser();

    FileType getFileTypeByExtension(const fs::path& aFile) const;

    /**
     * @brief Get the files that are stored inside the binary.
     *
     * @return std::vector<std::pair<std::string, size_t>> First is the name of the file.
     *                                                     Second is the offset to the file in the binary.
     */
    std::vector<std::pair<std::string, size_t>> getFilesInBinary();

    /**
     * @brief Export ZIP file that is stored inside the binary.
     *
     * @param aOutputPath Path to extract to.
     */
    void exportZipFiles(const fs::path& aOutputPath);

private:

    void openFile(const fs::path& aFile);

    void closeFile();

    /**
     * @brief Sets file stream offset to the beginning of the next ZIP file.
     *
     * @return true If ZIP was found.
     * @return false False if EoF was reached.
     */
    bool gotoNextZip();

    /**
     * @brief Extract ZIP container inside of binary file.
     *
     * @param aOutputPath Path where the ZIP and its content is saved to.
     * @param aComprZipSize Size of the compressed ZIP file.
     *                      If this value is zero, the function will determine
     *                      a suitable size itself. However, note that the
     *                      size is calculated from the current file offset
     *                      to the end of the file. This typically leads
     *                      to a large binary block trailing the actual ZIP
     *                      file. ZIP viewers/parsers typically ignore data
     *                      after the end of the ZIP, however this leads to
     *                      larger file sizes and leakage of unrelated information.
     *
     * @note The current offset in the file stream mIs needs to point
     *       to the beginning of the ZIP container.
     */
    void exportZip(const fs::path& aOutputPath, size_t aComprZipSize = 0u);


    FileType mFileType;
    FileFormatVersion mFileFormatVersion;

    fs::path mInputFile;
    size_t   mInputFileSize;

    DataStream mDs;

};


#endif // PARSER_H
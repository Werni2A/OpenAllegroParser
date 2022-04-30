
#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H


#include <filesystem>
#include <string>

// @todo Why does the compiler not find the lib? Check target_include_directory
#include "../../build/vcpkg_installed/x64-linux/include/tinyxml2.h"
// #include <tinyxml2.h>

#include "Parser.hpp"


namespace fs = std::filesystem;

using namespace tinyxml2;


class XmlGenerator
{
public:

    XmlGenerator(const PadFile& aPadFile, unsigned aExportVersion)
        : mExportVersion{aExportVersion}, mPadFile{aPadFile}, mXml{}
    { }

    std::string getFloatFmtFixAccuracy() const;
    std::string getFloatFmtAdjAccuracy() const;

    std::string getFloatFmtForTuple() const;

    std::string getFloatFmtForScalar() const;

    void generateXml();

    void exportToXml(const fs::path& aPathOut);

    void appendSymbol(XMLElement* aParent, const Symbol& aObj);

    void appendPad(XMLElement* aParent, const Pad& aObj, bool aUsrLayer);

private:

    // `padstack_editor.exe` versions, since the exported `*.pxml` file
    // slightly differs, depending on the software version.
    unsigned mExportVersion;

    const PadFile& mPadFile;
    XMLDocument mXml;

};


#endif // XMLGENERATOR_H
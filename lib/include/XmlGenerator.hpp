
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

    XmlGenerator(const PadFile& aPadFile) : mPadFile{aPadFile}, mXml{}
    { }

    void generateXml();

    void exportToXml(const fs::path& aPathOut);

private:

    const PadFile& mPadFile;
    XMLDocument mXml;

};


#endif // XMLGENERATOR_H
#include <filesystem>
#include <string>

#include <boost/program_options.hpp>

#include <Parser.hpp>
#include <XmlGenerator.hpp>


namespace fs = std::filesystem;
namespace po = boost::program_options;


void parseArgs(int argc, char* argv[], fs::path& input, bool& print, bool& extract, fs::path& output, bool& exportXml, unknownParam& uparam)
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h",                                             "produce help message")
        ("print,p",   po::bool_switch()->default_value(false), "print file content to terminal")
        ("extract,e", po::bool_switch()->default_value(false), "extract files from within the binary")
        ("input,i",   po::value<std::string>(),                "input file to parse")
        ("output,o",  po::value<std::string>(),                "output path (required iff extract is set)")
        ("export,x",  po::bool_switch()->default_value(false), "export XML file")

        ("unknownFlag",    po::bool_switch()->default_value(false), "flag for some unknown parameter 1")
        ("unknownFlag2",   po::bool_switch()->default_value(false), "flag for some unknown parameter 2")
        ("numUserLayers",  po::value<int>(),                        "number of user layers")
        ("additionalStr2", po::value<int>(),                        "number of additional strings e.g. symbol names")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);


    uparam.unknownFlag    = vm.count("unknownFlag")    ? vm["unknownFlag"].as<bool>()   : false;
    uparam.unknownFlag2   = vm.count("unknownFlag2")   ? vm["unknownFlag2"].as<bool>()  : false;
    uparam.numUserLayers  = vm.count("numUserLayers")  ? vm["numUserLayers"].as<int>()  : 0u;
    uparam.additionalStr2 = vm.count("additionalStr2") ? vm["additionalStr2"].as<int>() : 0u;


    if(vm.count("help"))
    {
        std::cout << desc << std::endl;
        std::exit(1);
    }

    print     = vm.count("print") ? vm["print"].as<bool>() : false;
    extract   = vm.count("extract") ? vm["extract"].as<bool>() : false;
    exportXml = vm.count("export") ? vm["export"].as<bool>() : false;

    if(vm.count("input"))
    {
        input = fs::path{vm["input"].as<std::string>()};
        if(!fs::exists(input))
        {
            std::cout << "The following input file was not found: " << input.string() << std::endl;
            std::cout << desc << std::endl;
            std::exit(1);
        }

        if(!fs::is_regular_file(input))
        {
            std::cout << "The following input is not a file: " << input.string() << std::endl;
            std::cout << desc << std::endl;
            std::exit(1);
        }
    }
    else
    {
        std::cout << "input was not specified but is required." << std::endl;
        std::cout << desc << std::endl;
        std::exit(1);
    }

    if(extract)
    {
        if(vm.count("output"))
        {
            output = fs::path{vm["output"].as<std::string>()};
            if(!fs::exists(output))
            {
                std::cout << "The following directory was not found: " << output.string() << std::endl;
                std::cout << desc << std::endl;
                std::exit(1);
            }

            if(!fs::is_directory(output))
            {
                std::cout << "The following path is not a directory: " << output << std::endl;
                std::cout << desc << std::endl;
                std::exit(1);
            }
        }
        else
        {
            std::cout << "output was not specified but is required, since extract is set." << std::endl;
            std::cout << desc << std::endl;
            std::exit(1);
        }
    }
}


int main(int argc, char* argv[])
{
    fs::path inputFile;
    bool     print;
    bool     extract;
    bool     exportXml;
    fs::path outputPath;

    unknownParam uparam;

    parseArgs(argc, argv, inputFile, print, extract, outputPath, exportXml, uparam);

    try
    {
        Parser parser{inputFile};

        const auto files = parser.getFilesInBinary();

        for(const auto& file : files)
        {
            const std::string& name   = file.first;
            const size_t&      offset = file.second;

            std::cout << "File found at 0x" << ToHex(offset, 8) << ": " << name << std::endl;
        }

        if(extract)
        {
            parser.exportZipFiles(outputPath);
        }
        else
        {
            try
            {
                PadFile padFile = parser.readPadFile(uparam);

                if(print)
                {
                    std::cout << "\r\n-----------------------------------------------" << std::endl;
                    std::cout << "--------------- File Content ------------------" << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << padFile << std::endl;
                }

                if(exportXml)
                {
                    const fs::path pathXmlRef    = inputFile.parent_path() / fs::path{inputFile.stem().string() + ".pxml"};
                    const fs::path pathXmlOutput = inputFile.parent_path() / fs::path{inputFile.stem().string() + "_export.pxml"};
                    std::cout << "Exporting XML to " << pathXmlOutput << " ..." << std::endl;

                    XmlGenerator xmlGenerator{padFile};
                    xmlGenerator.generateXml();
                    xmlGenerator.exportToXml(pathXmlOutput);
                }
            }
            catch(const std::exception& e)
            {
                throw std::runtime_error(std::string(e.what()) + "\r\nAt file offset 0x" + ToHex(parser.getCurrentOffset(), 8u));
            }
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "--------ERROR REPORT--------" << std::endl;
        std::cerr << e.what() << std::endl;
        std::exit(-1);
    }

    return 0;
}
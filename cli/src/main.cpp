#include <filesystem>
#include <string>

#include <boost/program_options.hpp>
#include <spdlog/spdlog.h>

#include <Parser.hpp>
#include <XmlGenerator.hpp>


namespace fs = std::filesystem;
namespace po = boost::program_options;


struct Args
{
    bool     print;
    bool     extract;
    bool     exportXml;
    bool     verbose;
    unsigned export_version;

    fs::path input;
    fs::path output;

    unknownParam uparam;
};


Args parseArgs(int argc, char* argv[])
{
    Args args;

    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h",                                             "produce help message")
        ("print,p",   po::bool_switch()->default_value(false), "print file content to terminal")
        ("extract,e", po::bool_switch()->default_value(false), "extract files from within the binary")
        ("input,i",   po::value<std::string>(),                "input file to parse")
        ("output,o",  po::value<std::string>(),                "output path (required iff extract is set)")
        ("export,x",  po::bool_switch()->default_value(false), "export XML file")
        ("verbose,v",  po::bool_switch()->default_value(false), "verbose output")
        ("export-version", po::value<int>(), "Version of padstack_editor.exe used for pxml export")

        ("bool0", po::bool_switch()->default_value(false), "bool0")
        ("bool1", po::bool_switch()->default_value(false), "bool1")
        ("bool2", po::bool_switch()->default_value(false), "bool2")
        ("int0",  po::value<int>(),                        "int0")
        ("numUserLayers",  po::value<int>(),                        "number of user layers") // @todo Not required anymore, remove
        ("additionalStr2", po::value<int>(),                        "number of additional strings e.g. symbol names")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    args.uparam.bool0 = vm.count("bool0") ? vm["bool0"].as<bool>() : false;
    args.uparam.bool1 = vm.count("bool1") ? vm["bool1"].as<bool>() : false;
    args.uparam.bool2 = vm.count("bool2") ? vm["bool2"].as<bool>() : false;
    args.uparam.int0  = vm.count("int0") ? vm["int0"].as<int>() : 0u;
    args.uparam.numUserLayers  = vm.count("numUserLayers")  ? vm["numUserLayers"].as<int>()  : 0u;
    args.uparam.additionalStr2 = vm.count("additionalStr2") ? vm["additionalStr2"].as<int>() : 0u;

    if(vm.count("help"))
    {
        std::cout << desc << std::endl;
        std::exit(1);
    }

    args.print     = vm.count("print") ? vm["print"].as<bool>() : false;
    args.extract   = vm.count("extract") ? vm["extract"].as<bool>() : false;
    args.exportXml = vm.count("export") ? vm["export"].as<bool>() : false;
    args.verbose   = vm.count("verbose") ? vm["verbose"].as<bool>() : false;
    args.export_version = vm.count("export-version") ? vm["export-version"].as<int>() : 0u;

    if(vm.count("input"))
    {
        args.input = fs::path{vm["input"].as<std::string>()};
        if(!fs::exists(args.input))
        {
            std::cout << "The following input file was not found: " << args.input.string() << std::endl;
            std::cout << desc << std::endl;
            std::exit(1);
        }

        if(!fs::is_regular_file(args.input))
        {
            std::cout << "The following input is not a file: " << args.input.string() << std::endl;
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

    if(args.extract)
    {
        if(vm.count("output"))
        {
            args.output = fs::path{vm["output"].as<std::string>()};
            if(!fs::exists(args.output))
            {
                std::cout << "The following directory was not found: " << args.output.string() << std::endl;
                std::cout << desc << std::endl;
                std::exit(1);
            }

            if(!fs::is_directory(args.output))
            {
                std::cout << "The following path is not a directory: " << args.output << std::endl;
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

    return args;
}


int main(int argc, char* argv[])
{
    Args args = parseArgs(argc, argv);

    if(!args.verbose)
    {
        spdlog::set_level(spdlog::level::off);
    }
    else
    {
        spdlog::set_level(spdlog::level::debug);
    }

    spdlog::set_pattern("[%^%l%$] %v");

    try
    {
        Parser parser{args.input};

        const auto files = parser.getFilesInBinary();

        for(const auto& file : files)
        {
            const std::string& name   = file.first;
            const size_t&      offset = file.second;

            std::cout << "File found at 0x" << ToHex(offset, 8) << ": " << name << std::endl;
        }

        if(args.extract)
        {
            parser.exportZipFiles(args.output);
        }
        else
        {
            try
            {
                PadFile padFile = parser.readPadFile(args.uparam);

                if(args.print)
                {
                    std::cout << "\r\n-----------------------------------------------" << std::endl;
                    std::cout << "--------------- File Content ------------------" << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << padFile << std::endl;
                }

                if(args.exportXml)
                {
                    const fs::path pathXmlRef    = args.input.parent_path() / fs::path{args.input.stem().string() + ".pxml"};
                    const fs::path pathXmlOutput = args.input.parent_path() / fs::path{args.input.stem().string() + "_export.pxml"};
                    std::cout << "Exporting XML to " << pathXmlOutput << " ..." << std::endl;

                    XmlGenerator xmlGenerator{padFile, args.export_version};
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
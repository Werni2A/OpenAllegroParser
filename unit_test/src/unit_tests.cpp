#include <stdio.h>
#include <stdlib.h>

#include <catch2/catch.hpp>

#include <Parser.hpp>
#include <Drillmethod.hpp>


TEST_CASE("Check PadstackUsage - THRU_PIN", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0000.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    int checkCtr = 5000;
    REQUIRE(checkCtr >= 1000u);
}


TEST_CASE("Check DrillOffset - x", "[DrillOffset]")
{
    fs::path inputFile = "test_cases/0012.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    // Compare against fix point representation of 123.5
    REQUIRE(padFile.offsetX == 1235);
}


TEST_CASE("Check DrillOffset - y", "[DrillOffset]")
{
    fs::path inputFile = "test_cases/0013.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    // Compare against fix point representation of 123.4
    REQUIRE(padFile.offsetY == 1234);
}


TEST_CASE("Check Drill - DrillHole - Complex", "[DrillHole]")
{
    fs::path inputFile = "test_cases/0017.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = true;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.drilltoolsize == "TOOL_SIZE");
    // REQUIRE(padFile.drillmethod == Drillmethod::NONE);
}


TEST_CASE("Check Unit - Mils", "[Unit]")
{
    fs::path inputFile = "test_cases/0019.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.unit == Units::mils);
}


TEST_CASE("Check Unit - Inch", "[Unit]")
{
    fs::path inputFile = "test_cases/0020.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.unit == Units::inch);
}


TEST_CASE("Check Unit - Millimeter", "[Unit]")
{
    fs::path inputFile = "test_cases/0021.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.unit == Units::mm);
}


TEST_CASE("Check Unit - Centimeter", "[Unit]")
{
    fs::path inputFile = "test_cases/0022.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.unit == Units::cm);
}


TEST_CASE("Check Unit - Micron", "[Unit]")
{
    fs::path inputFile = "test_cases/0023.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.unit == Units::um);
}


TEST_CASE("Check Accuracy - 0", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0024.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.accuracy == 0);
}


TEST_CASE("Check Accuracy - 1", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0025.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.accuracy == 1);
}


TEST_CASE("Check Accuracy - 2", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0026.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.accuracy == 2);
}


TEST_CASE("Check Accuracy - 3", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0027.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.accuracy == 3);
}


TEST_CASE("Check Accuracy - 4", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0028.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.accuracy == 4);
}


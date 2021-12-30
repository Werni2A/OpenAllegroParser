#include <stdio.h>
#include <stdlib.h>

#include <catch2/catch.hpp>

#include <Drillmethod.hpp>
#include <HoleType.hpp>
#include <Parser.hpp>


TEST_CASE("Check PadstackUsage - THRU_PIN", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0000.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::THRU_PIN);
}


TEST_CASE("Check PadstackUsage - SMD_PIN", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0001.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::SMD_PIN);
}


TEST_CASE("Check PadstackUsage - VIA", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0002.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::VIA);
}


TEST_CASE("Check PadstackUsage - BBVIA", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0003.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::BBVIA);
}


TEST_CASE("Check PadstackUsage - MICROVIA", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0004.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::MICROVIA);
}


TEST_CASE("Check PadstackUsage - SLOT", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0005.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::SLOT);
}


TEST_CASE("Check PadstackUsage - MECH_HOLE", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0006.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::MECH_HOLE);
}


TEST_CASE("Check PadstackUsage - TOOL_HOLE", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0007.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::TOOL_HOLE);
}


TEST_CASE("Check PadstackUsage - MOUNT_HOLE", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0008.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::MOUNT_HOLE);
}


TEST_CASE("Check PadstackUsage - FIDUCIAL", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0009.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::FIDUCIAL);
}


TEST_CASE("Check PadstackUsage - BOND_FINGER", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0010.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::BOND_FINGER);
}


TEST_CASE("Check PadstackUsage - DIE_PAD", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0011.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::DIE_PAD);
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

    REQUIRE(padFile.offsetX == 1235); // 123.5
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

    REQUIRE(padFile.offsetY == 1234); // 123.4
}


TEST_CASE("Check Drill Characters", "[Drill Characters]")
{
    fs::path inputFile = "test_cases/0014.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.characters == "FOO");
}


TEST_CASE("Check Drill Figure Width", "[Drill Figure Width]")
{
    fs::path inputFile = "test_cases/0015.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.width == 1234); // 123.4
}


// TEST_CASE("Check Drill Figure Height", "[Drill Figure Height]")
// {
//     fs::path inputFile = "test_cases/0016.pad";

//     Parser::unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.unknownFlag    = false;
//     uparam.additionalStr2 = 0;

//     Parser parser{inputFile};

//     PadFile padFile = parser.readPadFile(uparam);

//     REQUIRE(padFile.width == 1234); // 123.4
// }


TEST_CASE("Check Drill - DrillHole - Complex", "[DrillHole]")
{
    fs::path inputFile = "test_cases/0017.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = true;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.getDrillToolSize() == "TOOL_SIZE");
    REQUIRE(padFile.drillmethod == Drillmethod::NONE);
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


// TEST_CASE("Check Counter Bore - Complex", "[Complex]")
// {
//     fs::path inputFile = "test_cases/0029.pad";

//     Parser::unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.unknownFlag    = true;
//     uparam.additionalStr2 = 0;

//     Parser parser{inputFile};

//     PadFile padFile = parser.readPadFile(uparam);

//     REQUIRE(padFile.counter_drill_diameter == 12);
//     REQUIRE(padFile.counter_drill_positivetolerance == 1);
//     REQUIRE(padFile.counter_drill_negativetolerance == 2);
// }


// TEST_CASE("Check Drill Rows/Columns/Clearances - Complex", "[Complex]")
// {
//     fs::path inputFile = "test_cases/0032.pad";

//     Parser::unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.unknownFlag    = false;
//     uparam.additionalStr2 = 0;

//     Parser parser{inputFile};

//     PadFile padFile = parser.readPadFile(uparam);

//     REQUIRE(padFile.drill_columns == 5);
//     REQUIRE(padFile.drill_rows    == 6);

//     REQUIRE(padFile.clearance_columns == 12);
//     REQUIRE(padFile.clearance_rows    == 23);
// }



TEST_CASE("Check Drill Symbol Figure Type - None", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0033.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::NONE);
}


TEST_CASE("Check Drill Symbol Figure Type - Circle", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0034.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::CIRCLE);
}


TEST_CASE("Check Drill Symbol Figure Type - Square", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0035.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::SQUARE);
}


TEST_CASE("Check Drill Symbol Figure Type - Hexagon x", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0036.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::HEXAGONX);
}


TEST_CASE("Check Drill Symbol Figure Type - Hexagon y", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0037.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::HEXAGONY);
}


TEST_CASE("Check Drill Symbol Figure Type - Octagon", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0038.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::OCTAGON);
}


TEST_CASE("Check Drill Symbol Figure Type - Cross", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0039.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::CROSS);
}


TEST_CASE("Check Drill Symbol Figure Type - Diamond", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0040.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::DIAMOND);
}


TEST_CASE("Check Drill Symbol Figure Type - Triangle", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0041.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::TRIANGLE);
}


// @todo There is a bug in the Padstack Editor that prevents me from generating Oblong x figures
//       As a result the 0042.pad file is incorrect. This should should be adjusted in the future!
// TEST_CASE("Check Drill Symbol Figure Type - Oblong x", "[Drill Symbol Figure Type]")
// {
//     fs::path inputFile = "test_cases/0042.pad";

//     Parser::unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.unknownFlag    = false;
//     uparam.additionalStr2 = 0;

//     Parser parser{inputFile};

//     PadFile padFile = parser.readPadFile(uparam);

//     REQUIRE(padFile.figure == Figure::OBLONGX);
// }


TEST_CASE("Check Drill Symbol Figure Type - Oblong y", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0043.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::OBLONGY);
}


TEST_CASE("Check Drill Symbol Figure Type - Rectangle", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0044.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.figure == Figure::RECTANGLE);
}


TEST_CASE("Check Drill Hole Type - None", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0045.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::NONE);
}


TEST_CASE("Check Drill Hole Type - Circle", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0046.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::CIRCLE);
}


TEST_CASE("Check Drill Hole Type - Square", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0047.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::SQUARE);
}


TEST_CASE("Check Drill Hole Type - Oval Slot", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0048.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::OVAL_SLOT);
}


TEST_CASE("Check Drill Hole Type - Rectangular Slot", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0049.pad";

    Parser::unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.unknownFlag    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::RECT_SLOT);
}
#include <stdio.h>
#include <stdlib.h>

#include <catch2/catch.hpp>

#include <Drillmethod.hpp>
#include <HoleType.hpp>
#include <Parser.hpp>


TEST_CASE("Check PadstackUsage - THRU_PIN", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0000.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::THRU_PIN);
}


TEST_CASE("Check PadstackUsage - SMD_PIN", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0001.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::SMD_PIN);
}


TEST_CASE("Check PadstackUsage - VIA", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0002.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::VIA);
}


TEST_CASE("Check PadstackUsage - BBVIA", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0003.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::BBVIA);
}


TEST_CASE("Check PadstackUsage - MICROVIA", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0004.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::MICROVIA);
}


TEST_CASE("Check PadstackUsage - SLOT", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0005.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::SLOT);
}


TEST_CASE("Check PadstackUsage - MECH_HOLE", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0006.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::MECH_HOLE);
}


TEST_CASE("Check PadstackUsage - TOOL_HOLE", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0007.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::TOOL_HOLE);
}


TEST_CASE("Check PadstackUsage - MOUNT_HOLE", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0008.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::MOUNT_HOLE);
}


TEST_CASE("Check PadstackUsage - FIDUCIAL", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0009.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::FIDUCIAL);
}


TEST_CASE("Check PadstackUsage - BOND_FINGER", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0010.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::BOND_FINGER);
}


TEST_CASE("Check PadstackUsage - DIE_PAD", "[PadstackUsage]")
{
    fs::path inputFile = "test_cases/0011.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.padstackusage == PadstackUsage::DIE_PAD);
}


TEST_CASE("Check DrillOffset - x", "[DrillOffset]")
{
    fs::path inputFile = "test_cases/0012.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.offsetX == 1235); // 123.5
}


TEST_CASE("Check DrillOffset - y", "[DrillOffset]")
{
    fs::path inputFile = "test_cases/0013.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.offsetY == 1234); // 123.4
}


TEST_CASE("Check Drill Characters", "[Drill Characters]")
{
    fs::path inputFile = "test_cases/0014.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.characters == "FOO");
}


TEST_CASE("Check Drill Figure Width", "[Drill Figure Width]")
{
    fs::path inputFile = "test_cases/0015.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.width == 1234); // 123.4
}


// TEST_CASE("Check Drill Figure Height", "[Drill Figure Height]")
// {
//     fs::path inputFile = "test_cases/0016.pad";

//     unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.bool1    = false;
//     uparam.additionalStr2 = 0;

//     Parser parser{inputFile};

//     PadFile padFile = parser.readPadFile(uparam);

//     REQUIRE(padFile.width == 1234); // 123.4
// }


TEST_CASE("Check Drill - DrillHole - Complex", "[DrillHole]")
{
    fs::path inputFile = "test_cases/0017.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = true;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);


    REQUIRE(padFile.getDrillToolSize() == "TOOL_SIZE");
    REQUIRE(padFile.drillmethod == Drillmethod::NONE);
}


// @todo implement test_cases/0018.pad
// TEST_CASE("Check Generic Layers - Complex", "[Complex]")
// {
//     fs::path inputFile = "test_cases/0018.pad";

//     unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.bool1    = false;
//     uparam.additionalStr2 = 1;

//     Parser parser{inputFile};

//     PadFile padFile = parser.readPadFile(uparam);

//     for(int i = 0; i < padFile.preDefLayers.size(); ++i)
//     {
//         const auto& pad = padFile.preDefLayers[i];

//         switch(i)
//         {
//             case 3:
//                 {
//                     REQUIRE(pad.getWidth() == 11);
//                 }
//                 break;
//         }
//     }
// }


TEST_CASE("Check Unit - Mils", "[Unit]")
{
    fs::path inputFile = "test_cases/0019.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.unit == Units::mils);
}


TEST_CASE("Check Unit - Inch", "[Unit]")
{
    fs::path inputFile = "test_cases/0020.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.unit == Units::inch);
}


TEST_CASE("Check Unit - Millimeter", "[Unit]")
{
    fs::path inputFile = "test_cases/0021.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.unit == Units::mm);
}


TEST_CASE("Check Unit - Centimeter", "[Unit]")
{
    fs::path inputFile = "test_cases/0022.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.unit == Units::cm);
}


TEST_CASE("Check Unit - Micron", "[Unit]")
{
    fs::path inputFile = "test_cases/0023.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.unit == Units::um);
}


TEST_CASE("Check Accuracy - 0", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0024.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.accuracy == 0);
}


TEST_CASE("Check Accuracy - 1", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0025.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.accuracy == 1);
}


TEST_CASE("Check Accuracy - 2", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0026.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.accuracy == 2);
}


TEST_CASE("Check Accuracy - 3", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0027.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.accuracy == 3);
}


TEST_CASE("Check Accuracy - 4", "[Accuracy]")
{
    fs::path inputFile = "test_cases/0028.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.accuracy == 4);
}


// TEST_CASE("Check Counter Bore - Complex", "[Complex]")
// {
//     fs::path inputFile = "test_cases/0029.pad";

//     unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.bool1    = true;
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

//     unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.bool1    = false;
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

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::NONE);
}


TEST_CASE("Check Drill Symbol Figure Type - Circle", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0034.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::CIRCLE);
}


TEST_CASE("Check Drill Symbol Figure Type - Square", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0035.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::SQUARE);
}


TEST_CASE("Check Drill Symbol Figure Type - Hexagon x", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0036.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::HEXAGONX);
}


TEST_CASE("Check Drill Symbol Figure Type - Hexagon y", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0037.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::HEXAGONY);
}


TEST_CASE("Check Drill Symbol Figure Type - Octagon", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0038.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::OCTAGON);
}


TEST_CASE("Check Drill Symbol Figure Type - Cross", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0039.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::CROSS);
}


TEST_CASE("Check Drill Symbol Figure Type - Diamond", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0040.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::DIAMOND);
}


TEST_CASE("Check Drill Symbol Figure Type - Triangle", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0041.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::TRIANGLE);
}


// @todo There is a bug in the Padstack Editor that prevents me from generating Oblong x figures
//       As a result the 0042.pad file is incorrect. This should should be adjusted in the future!
// TEST_CASE("Check Drill Symbol Figure Type - Oblong x", "[Drill Symbol Figure Type]")
// {
//     fs::path inputFile = "test_cases/0042.pad";

//     unknownParam uparam;

//     uparam.numUserLayers  = 0;
//     uparam.bool1    = false;
//     uparam.additionalStr2 = 0;

//     Parser parser{inputFile};

//     PadFile padFile = parser.readPadFile(uparam);

//     REQUIRE(padFile.figure == Figure::OBLONGX);
// }


TEST_CASE("Check Drill Symbol Figure Type - Oblong y", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0043.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::OBLONGY);
}


TEST_CASE("Check Drill Symbol Figure Type - Rectangle", "[Drill Symbol Figure Type]")
{
    fs::path inputFile = "test_cases/0044.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.drillSymbol.figure == Figure::RECTANGLE);
}


TEST_CASE("Check Drill Hole Type - None", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0045.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::NONE);
}


TEST_CASE("Check Drill Hole Type - Circle", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0046.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::CIRCLE);
}


TEST_CASE("Check Drill Hole Type - Square", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0047.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::SQUARE);
}


TEST_CASE("Check Drill Hole Type - Oval Slot", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0048.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::OVAL_SLOT);
}


TEST_CASE("Check Drill Hole Type - Rectangular Slot", "[Drill Hole Type]")
{
    fs::path inputFile = "test_cases/0049.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::RECT_SLOT);
}


TEST_CASE("Check Drill Hole Type - Rectangular Slot - Complex", "[Complex]")
{
    fs::path inputFile = "test_cases/0050.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::RECT_SLOT);
    REQUIRE(padFile.slothole_width  == 50);
    REQUIRE(padFile.slothole_height == 60);
    REQUIRE(padFile.positivetolerance == 2);
    REQUIRE(padFile.negativetolerance == 3);
    REQUIRE(padFile.slothole_positivetolerancey == 4);
    REQUIRE(padFile.slothole_negativetolerancey == 5);

    REQUIRE(padFile.plated == true);
}


TEST_CASE("Check Drill Hole Type - Oval Slot - Complex", "[Complex]")
{
    fs::path inputFile = "test_cases/0051.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    REQUIRE(padFile.holeType == HoleType::OVAL_SLOT);
    REQUIRE(padFile.slothole_width  == 10);
    REQUIRE(padFile.slothole_height == 20);
    REQUIRE(padFile.positivetolerance == 1);
    REQUIRE(padFile.negativetolerance == 2);
    REQUIRE(padFile.slothole_positivetolerancey == 3);
    REQUIRE(padFile.slothole_negativetolerancey == 4);

    REQUIRE(padFile.plated == true);
}


TEST_CASE("0052: Check Predefined Layers - Complex", "[Complex]")
{
    fs::path inputFile = "test_cases/0052.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    // REGULAR_PAD - DEFAULT_INTERNAL
    REQUIRE(padFile.preDefLayers.at(3).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(3).getWidth()   == 101);
    REQUIRE(padFile.preDefLayers.at(3).getHeight()  == 101);
    REQUIRE(padFile.preDefLayers.at(3).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(3).getOffsetY() == 0);

    // THERMAL_PAD - DEFAULT_INTERNAL
    REQUIRE(padFile.preDefLayers.at(2).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(2).getWidth()   == 104);
    REQUIRE(padFile.preDefLayers.at(2).getHeight()  == 104);
    REQUIRE(padFile.preDefLayers.at(2).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(2).getOffsetY() == 0);

    // ANTIPAD_PAD - DEFAULT_INTERNAL
    REQUIRE(padFile.preDefLayers.at(1).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(1).getWidth()   == 107);
    REQUIRE(padFile.preDefLayers.at(1).getHeight()  == 107);
    REQUIRE(padFile.preDefLayers.at(1).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(1).getOffsetY() == 0);

    // KEEPOUT - DEFAULT_INTERNAL
    REQUIRE(padFile.preDefLayers.at(4).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(4).getWidth()   == 110);
    REQUIRE(padFile.preDefLayers.at(4).getHeight()  == 110);
    REQUIRE(padFile.preDefLayers.at(4).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(4).getOffsetY() == 0);

    // REGULAR_PAD - END_LAYER
    REQUIRE(padFile.preDefLayers.at(23).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(23).getWidth()   == 113);
    REQUIRE(padFile.preDefLayers.at(23).getHeight()  == 113);
    REQUIRE(padFile.preDefLayers.at(23).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(23).getOffsetY() == 0);

    // THERMAL_PAD - END_LAYER
    REQUIRE(padFile.preDefLayers.at(22).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(22).getWidth()   == 116);
    REQUIRE(padFile.preDefLayers.at(22).getHeight()  == 116);
    REQUIRE(padFile.preDefLayers.at(22).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(22).getOffsetY() == 0);

    // ANTIPAD_PAD - END_LAYER
    REQUIRE(padFile.preDefLayers.at(21).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(21).getWidth()   == 119);
    REQUIRE(padFile.preDefLayers.at(21).getHeight()  == 119);
    REQUIRE(padFile.preDefLayers.at(21).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(21).getOffsetY() == 0);

    // KEEPOUT - END_LAYER
    REQUIRE(padFile.preDefLayers.at(24).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(24).getWidth()   == 122);
    REQUIRE(padFile.preDefLayers.at(24).getHeight()  == 122);
    REQUIRE(padFile.preDefLayers.at(24).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(24).getOffsetY() == 0);

    // KEEPOUT - ADJACENT_KEEPOUT
    REQUIRE(padFile.preDefLayers.at(20).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(20).getWidth()   == 125);
    REQUIRE(padFile.preDefLayers.at(20).getHeight()  == 125);
    REQUIRE(padFile.preDefLayers.at(20).getOffsetX() == 126);
    REQUIRE(padFile.preDefLayers.at(20).getOffsetY() == 127);

    // REGULAR_PAD - TOP_SOLDER_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(14).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(14).getWidth()   == 128);
    REQUIRE(padFile.preDefLayers.at(14).getHeight()  == 128);
    REQUIRE(padFile.preDefLayers.at(14).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(14).getOffsetY() == 0);

    // REGULAR_PAD - BOTTOM_SOLDER_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(15).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(15).getWidth()   == 131);
    REQUIRE(padFile.preDefLayers.at(15).getHeight()  == 131);
    REQUIRE(padFile.preDefLayers.at(15).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(15).getOffsetY() == 0);

    // REGULAR_PAD - TOP_PASTE_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(16).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(16).getWidth()   == 134);
    REQUIRE(padFile.preDefLayers.at(16).getHeight()  == 134);
    REQUIRE(padFile.preDefLayers.at(16).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(16).getOffsetY() == 0);

    // REGULAR_PAD - BOTTOM_PASTE_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(17).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(17).getWidth()   == 137);
    REQUIRE(padFile.preDefLayers.at(17).getHeight()  == 137);
    REQUIRE(padFile.preDefLayers.at(17).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(17).getOffsetY() == 0);

    // REGULAR_PAD - TOP_FILM_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(18).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(18).getWidth()   == 140);
    REQUIRE(padFile.preDefLayers.at(18).getHeight()  == 140);
    REQUIRE(padFile.preDefLayers.at(18).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(18).getOffsetY() == 0);

    // REGULAR_PAD - BOTTOM_FILM_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(19).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(19).getWidth()   == 143);
    REQUIRE(padFile.preDefLayers.at(19).getHeight()  == 143);
    REQUIRE(padFile.preDefLayers.at(19).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(19).getOffsetY() == 0);

    // REGULAR_PAD - TOP_COVERLAY_PAD
    REQUIRE(padFile.preDefLayers.at(10).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(10).getWidth()   == 146);
    REQUIRE(padFile.preDefLayers.at(10).getHeight()  == 146);
    REQUIRE(padFile.preDefLayers.at(10).getOffsetX() == 147);
    REQUIRE(padFile.preDefLayers.at(10).getOffsetY() == 148);

    // REGULAR_PAD - BOTTOM_COVERLAY_PAD
    REQUIRE(padFile.preDefLayers.at(11).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(11).getWidth()   == 149);
    REQUIRE(padFile.preDefLayers.at(11).getHeight()  == 149);
    REQUIRE(padFile.preDefLayers.at(11).getOffsetX() == 150);
    REQUIRE(padFile.preDefLayers.at(11).getOffsetY() == 151);
}


TEST_CASE("0053: Check - Complex", "[Complex]")
{
    fs::path inputFile = "test_cases/0053.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 0;
    uparam.bool1    = false;
    uparam.additionalStr2 = 0;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    // REGULAR_PAD - DEFAULT_INTERNAL
    REQUIRE(padFile.preDefLayers.at(3).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(3).getWidth()   == 101);
    REQUIRE(padFile.preDefLayers.at(3).getHeight()  == 101);
    REQUIRE(padFile.preDefLayers.at(3).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(3).getOffsetY() == 0);

    // THERMAL_PAD - DEFAULT_INTERNAL
    REQUIRE(padFile.preDefLayers.at(2).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(2).getWidth()   == 104);
    REQUIRE(padFile.preDefLayers.at(2).getHeight()  == 104);
    REQUIRE(padFile.preDefLayers.at(2).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(2).getOffsetY() == 0);

    // ANTIPAD_PAD - DEFAULT_INTERNAL
    REQUIRE(padFile.preDefLayers.at(1).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(1).getWidth()   == 107);
    REQUIRE(padFile.preDefLayers.at(1).getHeight()  == 107);
    REQUIRE(padFile.preDefLayers.at(1).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(1).getOffsetY() == 0);

    // KEEPOUT - DEFAULT_INTERNAL
    REQUIRE(padFile.preDefLayers.at(4).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(4).getWidth()   == 110);
    REQUIRE(padFile.preDefLayers.at(4).getHeight()  == 110);
    REQUIRE(padFile.preDefLayers.at(4).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(4).getOffsetY() == 0);

    // REGULAR_PAD - END_LAYER
    REQUIRE(padFile.preDefLayers.at(23).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(23).getWidth()   == 113);
    REQUIRE(padFile.preDefLayers.at(23).getHeight()  == 113);
    REQUIRE(padFile.preDefLayers.at(23).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(23).getOffsetY() == 0);

    // THERMAL_PAD - END_LAYER
    REQUIRE(padFile.preDefLayers.at(22).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(22).getWidth()   == 116);
    REQUIRE(padFile.preDefLayers.at(22).getHeight()  == 116);
    REQUIRE(padFile.preDefLayers.at(22).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(22).getOffsetY() == 0);

    // ANTIPAD_PAD - END_LAYER
    REQUIRE(padFile.preDefLayers.at(21).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(21).getWidth()   == 119);
    REQUIRE(padFile.preDefLayers.at(21).getHeight()  == 119);
    REQUIRE(padFile.preDefLayers.at(21).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(21).getOffsetY() == 0);

    // KEEPOUT - END_LAYER
    REQUIRE(padFile.preDefLayers.at(24).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(24).getWidth()   == 122);
    REQUIRE(padFile.preDefLayers.at(24).getHeight()  == 122);
    REQUIRE(padFile.preDefLayers.at(24).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(24).getOffsetY() == 0);

    // KEEPOUT - ADJACENT_KEEPOUT
    REQUIRE(padFile.preDefLayers.at(20).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(20).getWidth()   == 125);
    REQUIRE(padFile.preDefLayers.at(20).getHeight()  == 125);
    REQUIRE(padFile.preDefLayers.at(20).getOffsetX() == 126);
    REQUIRE(padFile.preDefLayers.at(20).getOffsetY() == 127);

    // REGULAR_PAD - TOP_SOLDER_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(14).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(14).getWidth()   == 128);
    REQUIRE(padFile.preDefLayers.at(14).getHeight()  == 128);
    REQUIRE(padFile.preDefLayers.at(14).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(14).getOffsetY() == 0);

    // REGULAR_PAD - BOTTOM_SOLDER_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(15).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(15).getWidth()   == 131);
    REQUIRE(padFile.preDefLayers.at(15).getHeight()  == 131);
    REQUIRE(padFile.preDefLayers.at(15).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(15).getOffsetY() == 0);

    // REGULAR_PAD - TOP_PASTE_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(16).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(16).getWidth()   == 134);
    REQUIRE(padFile.preDefLayers.at(16).getHeight()  == 134);
    REQUIRE(padFile.preDefLayers.at(16).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(16).getOffsetY() == 0);

    // REGULAR_PAD - BOTTOM_PASTE_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(17).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(17).getWidth()   == 137);
    REQUIRE(padFile.preDefLayers.at(17).getHeight()  == 137);
    REQUIRE(padFile.preDefLayers.at(17).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(17).getOffsetY() == 0);

    // REGULAR_PAD - TOP_FILM_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(18).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(18).getWidth()   == 140);
    REQUIRE(padFile.preDefLayers.at(18).getHeight()  == 140);
    REQUIRE(padFile.preDefLayers.at(18).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(18).getOffsetY() == 0);

    // REGULAR_PAD - BOTTOM_FILM_MASK_PAD
    REQUIRE(padFile.preDefLayers.at(19).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(19).getWidth()   == 143);
    REQUIRE(padFile.preDefLayers.at(19).getHeight()  == 143);
    REQUIRE(padFile.preDefLayers.at(19).getOffsetX() == 0);
    REQUIRE(padFile.preDefLayers.at(19).getOffsetY() == 0);

    // REGULAR_PAD - TOP_COVERLAY_PAD
    REQUIRE(padFile.preDefLayers.at(10).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(10).getWidth()   == 146);
    REQUIRE(padFile.preDefLayers.at(10).getHeight()  == 146);
    REQUIRE(padFile.preDefLayers.at(10).getOffsetX() == 147);
    REQUIRE(padFile.preDefLayers.at(10).getOffsetY() == 148);

    // REGULAR_PAD - BOTTOM_COVERLAY_PAD
    REQUIRE(padFile.preDefLayers.at(11).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(11).getWidth()   == 149);
    REQUIRE(padFile.preDefLayers.at(11).getHeight()  == 149);
    REQUIRE(padFile.preDefLayers.at(11).getOffsetX() == 150);
    REQUIRE(padFile.preDefLayers.at(11).getOffsetY() == 151);

    // REGULAR_PAD - BACKDRILL_START
    REQUIRE(padFile.preDefLayers.at(5).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(5).getWidth()   == 152);
    REQUIRE(padFile.preDefLayers.at(5).getHeight()  == 152);
    REQUIRE(padFile.preDefLayers.at(5).getOffsetX() == 153);
    REQUIRE(padFile.preDefLayers.at(5).getOffsetY() == 154);

    // ANTIPAD_PAD - BACKDRILL_START
    REQUIRE(padFile.preDefLayers.at(6).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(6).getWidth()   == 155);
    REQUIRE(padFile.preDefLayers.at(6).getHeight()  == 155);
    REQUIRE(padFile.preDefLayers.at(6).getOffsetX() == 156);
    REQUIRE(padFile.preDefLayers.at(6).getOffsetY() == 157);

    // ANTIPAD_PAD - BACKDRILL_CLEARANCE
    REQUIRE(padFile.preDefLayers.at(8).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(8).getWidth()   == 158);
    REQUIRE(padFile.preDefLayers.at(8).getHeight()  == 158);
    REQUIRE(padFile.preDefLayers.at(8).getOffsetX() == 159);
    REQUIRE(padFile.preDefLayers.at(8).getOffsetY() == 160);

    // KEEPOUT - BACKDRILL_CLEARANCE
    REQUIRE(padFile.preDefLayers.at(7).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.preDefLayers.at(7).getWidth()   == 161);
    REQUIRE(padFile.preDefLayers.at(7).getHeight()  == 161);
    REQUIRE(padFile.preDefLayers.at(7).getOffsetX() == 162);
    REQUIRE(padFile.preDefLayers.at(7).getOffsetY() == 163);
}


TEST_CASE("0054: Check User defined Mask Layers - Complex", "[Complex]")
{
    fs::path inputFile = "test_cases/0054.pad";

    unknownParam uparam;

    uparam.numUserLayers  = 3;
    uparam.bool1    = false;
    uparam.additionalStr2 = 2;

    Parser parser{inputFile};

    PadFile padFile = parser.readPadFile(uparam);

    // USER_MASK - USER_STR
    REQUIRE(padFile.usrDefLayers.at(0).mUsrStr == "FOO_TOP");
    REQUIRE(padFile.usrDefLayers.at(0).getFigure()  == Figure::SHAPE_SYMBOL);
    REQUIRE(padFile.usrDefLayers.at(0).getShapeSymbolName() == "sha_sot89");
    REQUIRE(padFile.usrDefLayers.at(0).getWidth()   == 41);
    REQUIRE(padFile.usrDefLayers.at(0).getHeight()  == 17);

    // USER_MASK - USER_STR
    REQUIRE(padFile.usrDefLayers.at(1).mUsrStr == "FOO_BOTTOM");
    REQUIRE(padFile.usrDefLayers.at(1).getFigure()  == Figure::CIRCLE);
    REQUIRE(padFile.usrDefLayers.at(1).getWidth()   == 167);
    REQUIRE(padFile.usrDefLayers.at(1).getHeight()  == 167);
    REQUIRE(padFile.usrDefLayers.at(1).getOffsetX() == 0);
    REQUIRE(padFile.usrDefLayers.at(1).getOffsetY() == 0);

    // USER_MASK - USER_STR
    REQUIRE(padFile.usrDefLayers.at(2).mUsrStr == "BAR_TOP");
    REQUIRE(padFile.usrDefLayers.at(2).getFigure()  == Figure::SHAPE_SYMBOL);
    REQUIRE(padFile.usrDefLayers.at(2).getShapeSymbolName() == "sha_sot89msk");
    REQUIRE(padFile.usrDefLayers.at(2).getWidth()   == 44);
    REQUIRE(padFile.usrDefLayers.at(2).getHeight()  == 20);
}
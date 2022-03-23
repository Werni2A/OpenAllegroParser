#include <filesystem>
#include <string>

#include <fmt/core.h>
#include <fmt/printf.h>
// #include "../../build/vcpkg_installed/x64-linux/include/tinyxml2.h"
#include <tinyxml2.h>

#include "../include/XmlGenerator.hpp"

#include "../include/General.hpp"
#include "../include/Parser.hpp"


namespace fs = std::filesystem;

using namespace tinyxml2;


// @todo move to Function in General
// @todo Name           FixedPtToFloatPt(unsigned aAccuracy, uint32_t aFixedPt)
// @todo implement also FloatPtToFixedPt(unsigned aAccuracy, uint32_t aFloatPt)
template<typename T>
double new_to_fp(T aVal, const PadFile& aPadFile)
{
    return static_cast<double>(aVal) / std::pow(10.0, static_cast<double>(aPadFile.accuracy));
};


// Is hole type symmetrical along x- and y-axis.
bool is_xy_sym(const HoleType& aHoleType)
{
    switch(aHoleType)
    {
    case HoleType::CIRCLE:
    case HoleType::SQUARE:
        return true;
        break;

    case HoleType::OVAL_SLOT:
    case HoleType::RECT_SLOT:
        return false;
        break;

    case HoleType::NONE:
        throw std::invalid_argument("NONE is not a physical object!");

    default:
        throw std::invalid_argument(to_string(aHoleType) + " is not implemented!");
        break;
    }
}


void XmlGenerator::generateXml()
{
    // @todo move outside into a function get_float_format
    // const std::string float_format = fmt::sprintf("%%.%dg", aPadFile.accuracy);
    const std::string float_format = "%g";

    XMLDocument mXml;

    XMLDeclaration* std_declaration = mXml.NewDeclaration();

    mXml.InsertFirstChild(std_declaration);

    XMLNode* nPadstacks = mXml.NewElement("padstacks");
    mXml.InsertEndChild(nPadstacks);

    XMLElement* ePadstack = mXml.NewElement("padstack");
    ePadstack->SetAttribute("version", "1.0");
    nPadstacks->InsertEndChild(ePadstack);

    XMLElement* ePadstackname = mXml.NewElement("padstackname");
    std::string name = to_lower(mPadFile.getPadName());
    ePadstackname->SetText(name.c_str());
    ePadstack->InsertEndChild(ePadstackname);

    XMLElement* ePadstackusage = mXml.NewElement("padstackusage");
    ePadstackusage->SetText(to_string(mPadFile.padstackusage).c_str());
    ePadstack->InsertEndChild(ePadstackusage);

    XMLElement* eUnits = mXml.NewElement("units");
    eUnits->SetText(to_string(mPadFile.unit).c_str());
    ePadstack->InsertEndChild(eUnits);

    XMLElement* eAccuracy = mXml.NewElement("accuracy");
    eAccuracy->SetText(std::to_string(mPadFile.accuracy).c_str());
    ePadstack->InsertEndChild(eAccuracy);

    XMLElement* eDrillinfo = mXml.NewElement("drillinfo");
    ePadstack->InsertEndChild(eDrillinfo);

    {
        // void slotholeToXml(XMLElement* aNode, const PadFile& mPadFile);
        XMLElement* eSlothole = mXml.NewElement("slothole");
        eDrillinfo->InsertEndChild(eSlothole);

        XMLElement* eHoletype = mXml.NewElement("holetype");
        eHoletype->SetText(to_string(mPadFile.holeType).c_str());
        eSlothole->InsertEndChild(eHoletype);

        XMLElement* ePlating = mXml.NewElement("plating");
        const std::string yes_no = mPadFile.plated ? "Y" : "N";
        ePlating->SetText(yes_no.c_str());
        eSlothole->InsertEndChild(ePlating);

        XMLElement* eWidth = mXml.NewElement("width");
        eWidth->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.slothole_width, mPadFile)).c_str());
        eSlothole->InsertEndChild(eWidth);

        // For symmetrical holes we need only the length in one dimension.
        if(mPadFile.holeType != HoleType::NONE && !is_xy_sym(mPadFile.holeType))
        {
            XMLElement* eHeight = mXml.NewElement("height");
            eHeight->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.slothole_height, mPadFile)).c_str());
            eSlothole->InsertEndChild(eHeight);
        }

        XMLElement* ePositivetolerance = mXml.NewElement("positivetolerance");
        ePositivetolerance->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.positivetolerance, mPadFile)).c_str());
        eSlothole->InsertEndChild(ePositivetolerance);

        XMLElement* eNegativetolerance = mXml.NewElement("negativetolerance");
        eNegativetolerance->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.negativetolerance, mPadFile)).c_str());
        eSlothole->InsertEndChild(eNegativetolerance);

        XMLElement* eOffset = mXml.NewElement("offset");
        const std::string offsetX = fmt::sprintf(float_format, new_to_fp(mPadFile.offsetX, mPadFile));
        const std::string offsetY = fmt::sprintf(float_format, new_to_fp(mPadFile.offsetY, mPadFile));
        const std::string offset  = "(" + offsetX + ";" + offsetY + ")";
        eOffset->SetText(offset.c_str());
        eSlothole->InsertEndChild(eOffset);

        XMLElement* eDrilltoolsize = mXml.NewElement("drilltoolsize");
        eDrilltoolsize->SetText(mPadFile.getDrillToolSize().c_str());
        eSlothole->InsertEndChild(eDrilltoolsize);

        if(mPadFile.drillmethod != Drillmethod::NONE)
        {
            XMLElement* eDrillmethod = mXml.NewElement("drillmethod");
            eDrillmethod->SetText(to_string(mPadFile.drillmethod).c_str());
            eSlothole->InsertEndChild(eDrillmethod);
        }
    }

    if(mPadFile.drill_rows > 0u && mPadFile.drill_columns > 0u)
    {
        XMLElement* eMultidrill = mXml.NewElement("multidrill");
        eDrillinfo->InsertEndChild(eMultidrill);

        XMLElement* eRows = mXml.NewElement("rows");
        eRows->SetText(std::to_string(mPadFile.drill_rows).c_str());
        eMultidrill->InsertEndChild(eRows);

        XMLElement* eColumns = mXml.NewElement("columns");
        eColumns->SetText(std::to_string(mPadFile.drill_columns).c_str());
        eMultidrill->InsertEndChild(eColumns);

        XMLElement* eClearance = mXml.NewElement("clearance");
        const std::string clearanceRow = fmt::sprintf(float_format, new_to_fp(mPadFile.clearance_rows, mPadFile));
        const std::string clearanceCol = fmt::sprintf(float_format, new_to_fp(mPadFile.clearance_columns, mPadFile));
        const std::string clearance    = "(" + clearanceRow + ";" + clearanceCol + ")";
        eClearance->SetText(clearance.c_str());
        eMultidrill->InsertEndChild(eClearance);

        XMLElement* eStagger = mXml.NewElement("stagger");
        const std::string stagger = mPadFile.staggeredDrills ? "Y" : "N";
        eStagger->SetText(stagger.c_str());
        eMultidrill->InsertEndChild(eStagger);
    }

    {
        XMLElement* eDrillsymbol = mXml.NewElement("drillsymbol");
        eDrillinfo->InsertEndChild(eDrillsymbol);

        XMLElement* eFigure = mXml.NewElement("figure");
        eFigure->SetText(to_string(mPadFile.figure).c_str());
        eDrillsymbol->InsertEndChild(eFigure);

        XMLElement* eCharacters = mXml.NewElement("characters");
        eCharacters->SetText(mPadFile.characters.c_str());
        eDrillsymbol->InsertEndChild(eCharacters);

        XMLElement* eWidth = mXml.NewElement("width");
        eWidth->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.width, mPadFile)).c_str());
        eDrillsymbol->InsertEndChild(eWidth);

        XMLElement* eHeight = mXml.NewElement("height");
        eHeight->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.height, mPadFile)).c_str());
        eDrillsymbol->InsertEndChild(eHeight);
    }

    if(mPadFile.back_drill_figure != Figure::NONE)
    {
        XMLElement* eBackdrill = mXml.NewElement("backdrill");
        eDrillinfo->InsertEndChild(eBackdrill);

        // @todo implement
        XMLElement* eDiameter = mXml.NewElement("diameter");
        // eDiameter->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.back_drill_diameter, mPadFile)).c_str());
        eDiameter->SetText("TODO");
        eBackdrill->InsertEndChild(eDiameter);

        {
            XMLElement* eDrillsymbol = mXml.NewElement("drillsymbol");
            eBackdrill->InsertEndChild(eDrillsymbol);

            XMLElement* eFigure = mXml.NewElement("figure");
            eFigure->SetText(to_string(mPadFile.back_drill_figure).c_str());
            eDrillsymbol->InsertEndChild(eFigure);

            XMLElement* eCharacters = mXml.NewElement("characters");
            eCharacters->SetText(mPadFile.back_drill_characters.c_str());
            eDrillsymbol->InsertEndChild(eCharacters);

            XMLElement* eWidth = mXml.NewElement("width");
            eWidth->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.back_drill_figure_width, mPadFile)).c_str());
            eDrillsymbol->InsertEndChild(eWidth);

            XMLElement* eHeight = mXml.NewElement("height");
            eHeight->SetText(fmt::sprintf(float_format, new_to_fp(mPadFile.back_drill_figure_height, mPadFile)).c_str());
            eDrillsymbol->InsertEndChild(eHeight);
        }
    }

    for(const auto& pad : mPadFile.preDefLayers)
    {
        if(pad.getFigure() == Figure::NONE || pad.getType() == Type::UNKNOWN)
        {
            continue;
        }

        XMLElement* ePad = mXml.NewElement("pad");
        ePadstack->InsertEndChild(ePad);

        XMLElement* eType = mXml.NewElement("type");
        eType->SetText(to_string(pad.getType()).c_str());
        ePad->InsertEndChild(eType);

        XMLElement* eLayer = mXml.NewElement("layer");
        eLayer->SetText(to_string(pad.getLayer()).c_str());
        ePad->InsertEndChild(eLayer);

        XMLElement* eFigure = mXml.NewElement("figure");
        std::string figure = (pad.getFigure() == Figure::OBLONGX) ? "OBLONG" : to_string(pad.getFigure());
        eFigure->SetText(figure.c_str());
        ePad->InsertEndChild(eFigure);

        if(pad.getOffsetX() != 0 || pad.getOffsetY() != 0)
        {
            XMLElement* eOffset = mXml.NewElement("offset");
            const std::string offsetX = fmt::sprintf(float_format, new_to_fp(pad.getOffsetX(), mPadFile));
            const std::string offsetY = fmt::sprintf(float_format, new_to_fp(pad.getOffsetY(), mPadFile));
            const std::string offset  = "(" + offsetX + ";" + offsetY + ")";
            eOffset->SetText(offset.c_str());
            ePad->InsertEndChild(eOffset);
        }

        XMLElement* eWidth = mXml.NewElement("width");
        eWidth->SetText(fmt::sprintf(float_format, new_to_fp(pad.getWidth(), mPadFile)).c_str());
        ePad->InsertEndChild(eWidth);

        XMLElement* eHeight = mXml.NewElement("height");
        eHeight->SetText(fmt::sprintf(float_format, new_to_fp(pad.getHeight(), mPadFile)).c_str());
        ePad->InsertEndChild(eHeight);

        if(pad.getNsides() != 0)
        {
            XMLElement* eNsides = mXml.NewElement("nsides");
            eNsides->SetText(std::to_string(pad.getNsides()).c_str());
            ePad->InsertEndChild(eNsides);
        }

        if(pad.getCorner() != 0)
        {
            XMLElement* eCorner = mXml.NewElement("corner");
            eCorner->SetText(fmt::sprintf(float_format, new_to_fp(pad.getCorner(), mPadFile)).c_str());
            ePad->InsertEndChild(eCorner);
        }

        if(pad.isUpperLeftCornerSpecial())
        {
            XMLElement* eUl = mXml.NewElement("ul");
            eUl->SetText(std::string{'Y'}.c_str());
            ePad->InsertEndChild(eUl);
        }

        if(pad.isUpperRightCornerSpecial())
        {
            XMLElement* eUr = mXml.NewElement("ur");
            eUr->SetText(std::string{'Y'}.c_str());
            ePad->InsertEndChild(eUr);
        }

        if(pad.isLowerLeftCornerSpecial())
        {
            XMLElement* eLl = mXml.NewElement("ll");
            eLl->SetText(std::string{'Y'}.c_str());
            ePad->InsertEndChild(eLl);
        }

        if(pad.isLowerRightCornerSpecial())
        {
            XMLElement* eLr = mXml.NewElement("lr");
            eLr->SetText(std::string{'Y'}.c_str());
            ePad->InsertEndChild(eLr);
        }
    }


    for(const auto& pad : mPadFile.usrDefLayers)
    {
        if(pad.getFigure() == Figure::NONE || pad.getType() == Type::UNKNOWN)
        {
            continue;
        }

        XMLElement* ePad = mXml.NewElement("pad");
        ePadstack->InsertEndChild(ePad);

        XMLElement* eType = mXml.NewElement("type");
        eType->SetText(to_string(pad.getType()).c_str());
        ePad->InsertEndChild(eType);

        XMLElement* eLayer = mXml.NewElement("layer");
        eLayer->SetText(pad.mUsrStr.c_str());
        ePad->InsertEndChild(eLayer);

        XMLElement* eFigure = mXml.NewElement("figure");
        std::string figure = (pad.getFigure() == Figure::OBLONGX) ? "OBLONG" : to_string(pad.getFigure());
        eFigure->SetText(figure.c_str());
        ePad->InsertEndChild(eFigure);

        if(pad.getOffsetX() != 0 || pad.getOffsetY() != 0)
        {
            XMLElement* eOffset = mXml.NewElement("offset");
            const std::string offsetX = fmt::sprintf(float_format, new_to_fp(pad.getOffsetX(), mPadFile));
            const std::string offsetY = fmt::sprintf(float_format, new_to_fp(pad.getOffsetY(), mPadFile));
            const std::string offset  = "(" + offsetX + ";" + offsetY + ")";
            eOffset->SetText(offset.c_str());
            ePad->InsertEndChild(eOffset);
        }

        XMLElement* eWidth = mXml.NewElement("width");
        eWidth->SetText(fmt::sprintf(float_format, new_to_fp(pad.getWidth(), mPadFile)).c_str());
        ePad->InsertEndChild(eWidth);

        XMLElement* eHeight = mXml.NewElement("height");
        eHeight->SetText(fmt::sprintf(float_format, new_to_fp(pad.getHeight(), mPadFile)).c_str());
        ePad->InsertEndChild(eHeight);

        if(pad.getNsides() != 0)
        {
            XMLElement* eNsides = mXml.NewElement("nsides");
            eNsides->SetText(std::to_string(pad.getNsides()).c_str());
            ePad->InsertEndChild(eNsides);
        }

        if(pad.getCorner() != 0)
        {
            XMLElement* eCorner = mXml.NewElement("corner");
            eCorner->SetText(fmt::sprintf(float_format, new_to_fp(pad.getCorner(), mPadFile)).c_str());
            ePad->InsertEndChild(eCorner);
        }

        if(pad.isUpperLeftCornerSpecial())
        {
            XMLElement* eUl = mXml.NewElement("ul");
            eUl->SetText(std::string{'Y'}.c_str());
            ePad->InsertEndChild(eUl);
        }

        if(pad.isUpperRightCornerSpecial())
        {
            XMLElement* eUr = mXml.NewElement("ur");
            eUr->SetText(std::string{'Y'}.c_str());
            ePad->InsertEndChild(eUr);
        }

        if(pad.isLowerLeftCornerSpecial())
        {
            XMLElement* eLl = mXml.NewElement("ll");
            eLl->SetText(std::string{'Y'}.c_str());
            ePad->InsertEndChild(eLl);
        }

        if(pad.isLowerRightCornerSpecial())
        {
            XMLElement* eLr = mXml.NewElement("lr");
            eLr->SetText(std::string{'Y'}.c_str());
            ePad->InsertEndChild(eLr);
        }
    }
}


void XmlGenerator::exportToXml(const fs::path& aPathOut)
{
    XMLError result = mXml.SaveFile(aPathOut.c_str());

    if(result != XML_SUCCESS)
    {
        throw std::runtime_error("Saving XML file to " + aPathOut.string()
            + " failed with error code " + std::to_string(result) + "!");
    }
}
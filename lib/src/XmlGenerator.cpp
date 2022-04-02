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

void XmlGenerator::appendSymbol(XMLElement* aParent, const Symbol& aObj)
{
    // @todo move outside into a function get_float_format
    // const std::string float_format = fmt::sprintf("%%.%dg", aPadFile.accuracy);
    const std::string float_format = "%g";

    XMLElement* eFigure = mXml.NewElement("figure");
    eFigure->SetText(to_string(aObj.figure, true).c_str());
    aParent->InsertEndChild(eFigure);

    if(!aObj.characters.empty())
    {
        XMLElement* eCharacters = mXml.NewElement("characters");
        eCharacters->SetText(aObj.characters.c_str());
        aParent->InsertEndChild(eCharacters);
    }

    XMLElement* eWidth = mXml.NewElement("width");
    eWidth->SetText(fmt::sprintf(float_format, mPadFile.FixedPtToFloatPt(aObj.width)).c_str());
    aParent->InsertEndChild(eWidth);

    if(aObj.height != 0u)
    {
        XMLElement* eHeight = mXml.NewElement("height");
        eHeight->SetText(fmt::sprintf(float_format, mPadFile.FixedPtToFloatPt(aObj.height)).c_str());
        aParent->InsertEndChild(eHeight);
    }
}


void XmlGenerator::appendPad(XMLElement* aParent, const Pad& aObj, bool aUsrLayer)
{
    XMLElement* eType = mXml.NewElement("type");
    eType->SetText(to_string(aObj.getType()).c_str());
    aParent->InsertEndChild(eType);

    XMLElement* eLayer = mXml.NewElement("layer");
    const std::string layer = aUsrLayer ? aObj.mUsrStr.c_str() : to_string(aObj.getLayer());
    eLayer->SetText(layer.c_str());
    aParent->InsertEndChild(eLayer);

    if(aObj.getFigure() != Figure::NONE)
    {
        XMLElement* eFigure = mXml.NewElement("figure");
        std::string figure = to_string(aObj.getFigure(), true);
        eFigure->SetText(figure.c_str());
        aParent->InsertEndChild(eFigure);

        if(aObj.getOffsetX() != 0 || aObj.getOffsetY() != 0)
        {
            XMLElement* eOffset = mXml.NewElement("offset");
            const std::string offsetX = fmt::sprintf(getFloatFmtForTuple(), mPadFile.FixedPtToFloatPt(aObj.getOffsetX()));
            const std::string offsetY = fmt::sprintf(getFloatFmtForTuple(), mPadFile.FixedPtToFloatPt(aObj.getOffsetY()));
            const std::string offset  = "(" + offsetX + ";" + offsetY + ")";
            eOffset->SetText(offset.c_str());
            aParent->InsertEndChild(eOffset);
        }

        if(!aObj.getShapeSymbolName().empty())
        {
            XMLElement* eShapename = mXml.NewElement("shapename");
            eShapename->SetText(aObj.getShapeSymbolName().c_str());
            aParent->InsertEndChild(eShapename);
        }

        if(!aObj.getFlashName().empty())
        {
            XMLElement* eFlashname = mXml.NewElement("flashname");
            eFlashname->SetText(aObj.getFlashName().c_str());
            aParent->InsertEndChild(eFlashname);
        }

        XMLElement* eWidth = mXml.NewElement("width");
        eWidth->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(aObj.getWidth())).c_str());
        aParent->InsertEndChild(eWidth);

        XMLElement* eHeight = mXml.NewElement("height");
        eHeight->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(aObj.getHeight())).c_str());
        aParent->InsertEndChild(eHeight);

        if(aObj.getNsides() != 0)
        {
            XMLElement* eNsides = mXml.NewElement("nsides");
            eNsides->SetText(std::to_string(aObj.getNsides()).c_str());
            aParent->InsertEndChild(eNsides);
        }

        if(aObj.getCorner() != 0)
        {
            XMLElement* eCorner = mXml.NewElement("corner");
            eCorner->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(aObj.getCorner())).c_str());
            aParent->InsertEndChild(eCorner);
        }

        if(aObj.isUpperLeftCornerSpecial())
        {
            XMLElement* eUl = mXml.NewElement("ul");
            eUl->SetText(std::string{'Y'}.c_str());
            aParent->InsertEndChild(eUl);
        }

        if(aObj.isUpperRightCornerSpecial())
        {
            XMLElement* eUr = mXml.NewElement("ur");
            eUr->SetText(std::string{'Y'}.c_str());
            aParent->InsertEndChild(eUr);
        }

        if(aObj.isLowerLeftCornerSpecial())
        {
            XMLElement* eLl = mXml.NewElement("ll");
            eLl->SetText(std::string{'Y'}.c_str());
            aParent->InsertEndChild(eLl);
        }

        if(aObj.isLowerRightCornerSpecial())
        {
            XMLElement* eLr = mXml.NewElement("lr");
            eLr->SetText(std::string{'Y'}.c_str());
            aParent->InsertEndChild(eLr);
        }
    }
}


std::string XmlGenerator::getFloatFmtForTuple() const
{
    // Fixed floating point accuracy
    const std::string float_fmt_fix_acc = fmt::sprintf("%%.%df", mPadFile.accuracy);
    // Adjusted floating point accuracy
    const std::string float_fmt_adj_acc = "%g";

    return float_fmt_fix_acc;
}


std::string XmlGenerator::getFloatFmtForScalar() const
{
    // Fixed floating point accuracy
    const std::string float_fmt_fix_acc = fmt::sprintf("%%.%df", mPadFile.accuracy);
    // Adjusted floating point accuracy
    const std::string float_fmt_adj_acc = "%g";

    return float_fmt_fix_acc;
}


void XmlGenerator::generateXml()
{
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

    if(mPadFile.holeType != HoleType::NONE || mPadFile.drillSymbol.figure != Figure::NONE || mPadFile.backDrillSymbol.figure != Figure::NONE)
    {
        XMLElement* eDrillinfo = mXml.NewElement("drillinfo");
        ePadstack->InsertEndChild(eDrillinfo);

        if(mPadFile.holeType != HoleType::NONE)
        {
            // void slotholeToXml(XMLElement* aNode, const PadFile& mPadFile);
            XMLElement* eSlothole = mXml.NewElement("slothole");
            eDrillinfo->InsertEndChild(eSlothole);

            XMLElement* eHoletype = mXml.NewElement("holetype");
            eHoletype->SetText(to_string(mPadFile.holeType).c_str());
            eSlothole->InsertEndChild(eHoletype);

            if(mPadFile.plated)
            {
                XMLElement* ePlating = mXml.NewElement("plating");
                const std::string yes_no = mPadFile.plated ? "Y" : "N";
                ePlating->SetText(yes_no.c_str());
                eSlothole->InsertEndChild(ePlating);
            }

            XMLElement* eWidth = mXml.NewElement("width");
            eWidth->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.slothole_width)).c_str());
            eSlothole->InsertEndChild(eWidth);

            // For symmetrical holes we need only the length in one dimension.
            if(mPadFile.holeType != HoleType::NONE && !is_xy_sym(mPadFile.holeType))
            {
                XMLElement* eHeight = mXml.NewElement("height");
                eHeight->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.slothole_height)).c_str());
                eSlothole->InsertEndChild(eHeight);
            }

            if(mPadFile.positivetolerance != 0)
            {
                XMLElement* ePositivetolerance = mXml.NewElement("positivetolerance");
                ePositivetolerance->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.positivetolerance)).c_str());
                eSlothole->InsertEndChild(ePositivetolerance);
            }

            if(mPadFile.negativetolerance != 0)
            {
                XMLElement* eNegativetolerance = mXml.NewElement("negativetolerance");
                eNegativetolerance->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.negativetolerance)).c_str());
                eSlothole->InsertEndChild(eNegativetolerance);
            }

            if(mPadFile.offsetX != 0 || mPadFile.offsetY != 0)
            {
                XMLElement* eOffset = mXml.NewElement("offset");
                const std::string offsetX = fmt::sprintf(getFloatFmtForTuple(), mPadFile.FixedPtToFloatPt(mPadFile.offsetX));
                const std::string offsetY = fmt::sprintf(getFloatFmtForTuple(), mPadFile.FixedPtToFloatPt(mPadFile.offsetY));
                const std::string offset  = "(" + offsetX + ";" + offsetY + ")";
                eOffset->SetText(offset.c_str());
                eSlothole->InsertEndChild(eOffset);
            }

            if(!mPadFile.getDrillToolSize().empty())
            {
                XMLElement* eDrilltoolsize = mXml.NewElement("drilltoolsize");
                eDrilltoolsize->SetText(mPadFile.getDrillToolSize().c_str());
                eSlothole->InsertEndChild(eDrilltoolsize);
            }

            if(mPadFile.drillmethod != Drillmethod::NONE)
            {
                XMLElement* eDrillmethod = mXml.NewElement("drillmethod");
                eDrillmethod->SetText(to_string(mPadFile.drillmethod).c_str());
                eSlothole->InsertEndChild(eDrillmethod);
            }
        }

        if(mPadFile.drill_rows != 1u || mPadFile.drill_columns != 1u)
        {
            XMLElement* eMultidrill = mXml.NewElement("multidrill");
            eDrillinfo->InsertEndChild(eMultidrill);

            if(mPadFile.drill_rows != 1u)
            {
                XMLElement* eRows = mXml.NewElement("rows");
                eRows->SetText(std::to_string(mPadFile.drill_rows).c_str());
                eMultidrill->InsertEndChild(eRows);
            }

            if(mPadFile.drill_columns != 1u)
            {
                XMLElement* eColumns = mXml.NewElement("columns");
                eColumns->SetText(std::to_string(mPadFile.drill_columns).c_str());
                eMultidrill->InsertEndChild(eColumns);
            }

            if(mPadFile.clearance_rows != 0 || mPadFile.clearance_columns != 0)
            {
                XMLElement* eClearance = mXml.NewElement("clearance");
                const std::string clearanceRow = fmt::sprintf(getFloatFmtForTuple(), mPadFile.FixedPtToFloatPt(mPadFile.clearance_rows));
                const std::string clearanceCol = fmt::sprintf(getFloatFmtForTuple(), mPadFile.FixedPtToFloatPt(mPadFile.clearance_columns));
                const std::string clearance    = "(" + clearanceRow + ";" + clearanceCol + ")";
                eClearance->SetText(clearance.c_str());
                eMultidrill->InsertEndChild(eClearance);
            }

            if(mPadFile.staggeredDrills)
            {
                XMLElement* eStagger = mXml.NewElement("stagger");
                const std::string stagger = mPadFile.staggeredDrills ? "Y" : "N";
                eStagger->SetText(stagger.c_str());
                eMultidrill->InsertEndChild(eStagger);
            }
        }

        {
            XMLElement* eDrillsymbol = mXml.NewElement("drillsymbol");
            eDrillinfo->InsertEndChild(eDrillsymbol);

            appendSymbol(eDrillsymbol, mPadFile.drillSymbol);
        }

        if(mPadFile.backDrillSymbol.figure != Figure::NONE)
        {
            XMLElement* eBackdrill = mXml.NewElement("backdrill");
            eDrillinfo->InsertEndChild(eBackdrill);

            XMLElement* eDiameter = mXml.NewElement("diameter");
            eDiameter->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.diameter)).c_str());
            eBackdrill->InsertEndChild(eDiameter);

            if(mPadFile.backDrillSymbol.figure != Figure::NONE)
            {
                XMLElement* eDrillsymbol = mXml.NewElement("drillsymbol");
                eBackdrill->InsertEndChild(eDrillsymbol);

                appendSymbol(eDrillsymbol, mPadFile.backDrillSymbol);
            }
        }

        if(mPadFile.counter_drill_diameter != 0)
        {
            XMLElement* eCounterboresink = mXml.NewElement("counterboresink");
            eDrillinfo->InsertEndChild(eCounterboresink);

            XMLElement* eDiameter = mXml.NewElement("diameter");
            eDiameter->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.counter_drill_diameter)).c_str());
            eCounterboresink->InsertEndChild(eDiameter);

            if(mPadFile.counter_drill_positivetolerance != 0)
            {
                XMLElement* ePositivetolerance = mXml.NewElement("positivetolerance");
                ePositivetolerance->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.counter_drill_positivetolerance)).c_str());
                eCounterboresink->InsertEndChild(ePositivetolerance);
            }

            if(mPadFile.counter_drill_negativetolerance != 0)
            {
                XMLElement* eNegativetolerance = mXml.NewElement("negativetolerance");
                eNegativetolerance->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.counter_drill_negativetolerance)).c_str());
                eCounterboresink->InsertEndChild(eNegativetolerance);
            }

            XMLElement* eCounterangle = mXml.NewElement("counterangle");
            eCounterangle->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.counterangle)).c_str());
            eCounterboresink->InsertEndChild(eCounterangle);

            XMLElement* eCounterdepth = mXml.NewElement("counterdepth");
            // @todo figur out where counterdepth is stored
            // eCounterdepth->SetText(fmt::sprintf(getFloatFmtForScalar(), mPadFile.FixedPtToFloatPt(mPadFile.counterdepth)).c_str());
            eCounterboresink->InsertEndChild(eCounterdepth);
        }
    }

    for(const auto& pad : mPadFile.preDefLayers)
    {
        if(pad.getFigure() != Figure::NONE && pad.getType() != Type::UNKNOWN)
        {
            XMLElement* ePad = mXml.NewElement("pad");
            ePadstack->InsertEndChild(ePad);

            appendPad(ePad, pad, false);
        }
    }

    for(const auto& pad : mPadFile.usrDefLayers)
    {
        if(pad.getFigure() != Figure::NONE && pad.getType() != Type::UNKNOWN)
        {
            XMLElement* ePad = mXml.NewElement("pad");
            ePadstack->InsertEndChild(ePad);

            appendPad(ePad, pad, true);
        }
    }

    if(mPadFile.isPolyVia || mPadFile.lock_layer_span)
    {
        XMLElement* eOptions = mXml.NewElement("options");
        ePadstack->InsertEndChild(eOptions);

        if(mPadFile.isPolyVia)
        {
            XMLElement* ePolyVia = mXml.NewElement("poly_via");
            const std::string polyVia = mPadFile.isPolyVia ? "Y" : "N";
            ePolyVia->SetText(polyVia.c_str());
            eOptions->InsertEndChild(ePolyVia);
        }

        if(mPadFile.lock_layer_span)
        {
            XMLElement* eLockLayerSpan = mXml.NewElement("lock_layer_span");
            const std::string lockLayerSpan = mPadFile.lock_layer_span ? "Y" : "N";
            eLockLayerSpan->SetText(lockLayerSpan.c_str());
            eOptions->InsertEndChild(eLockLayerSpan);
        }

        if(!mPadFile.not_suppress_nc_internal_pads)
        {
            XMLElement* eSupressUnconnected = mXml.NewElement("supress_unconnected");
            const std::string polyVia = !mPadFile.not_suppress_nc_internal_pads ? "Y" : "N";
            eSupressUnconnected->SetText(polyVia.c_str());
            eOptions->InsertEndChild(eSupressUnconnected);
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
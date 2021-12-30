#ifndef PADFILE_HPP
#define PADFILE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "Drillmethod.hpp"
#include "Figure.hpp"
#include "General.hpp"
#include "HoleType.hpp"
#include "Pad.hpp"
#include "PadstackUsage.hpp"
#include "Units.hpp"


class PadFile
{
public:

    std::string getPadName() const
    {
        const uint32_t idx = strIdxPadName;

        const auto findEntry = [idx] (std::pair<int, std::string> aIdxStrPair) -> bool
            {
                return aIdxStrPair.first == idx;
            };

        const auto it = std::find_if(idxStrPairLst.cbegin(), idxStrPairLst.cend(), findEntry);

        if(it == idxStrPairLst.cend())
        {
            throw std::runtime_error("Index " + std::to_string(idx) + " not found!");
        }

        return it->second;
    }


    std::string getDrillToolSize() const
    {
        const uint32_t idx = strIdxDrillToolSize;

        const auto findEntry = [idx] (std::pair<int, std::string> aIdxStrPair) -> bool
            {
                return aIdxStrPair.first == idx;
            };

        const auto it = std::find_if(idxStrPairLst.cbegin(), idxStrPairLst.cend(), findEntry);

        if(it == idxStrPairLst.cend())
        {
            throw std::runtime_error("Index " + std::to_string(idx) + " not found!");
        }

        return it->second;
    }


    std::string swVersion;

    uint16_t accuracy;
    Units unit;

    // @todo Figure out how the structure works and replace the vector
    //       with a map with indicies of std::any or std::string
    std::vector<std::pair<int, std::string>> idxStrPairLst;

    uint32_t strIdxPadName;
    uint32_t idxUnknown;
    uint32_t strIdxDrillToolSize;

    Drillmethod drillmethod;

    HoleType holeType;
    bool     staggeredDrills;
    bool     plated;

    bool not_suppress_nc_internal_pads;
    bool isPolyVia;

    PadstackUsage padstackusage;

    uint16_t drill_rows;
    uint16_t drill_columns;

    bool lock_layer_span;

    int32_t offsetX;
    int32_t offsetY;

    uint32_t clearance_columns;
    uint32_t clearance_rows;

    int32_t finished_size;

    int32_t positivetolerance;
    int32_t negativetolerance;

    uint32_t slothole_width;
    uint32_t slothole_height;
    int32_t slothole_positivetolerancey;
    int32_t slothole_negativetolerancey;

    uint32_t width;
    uint32_t height;

    Figure figure;
    std::string characters;

    uint32_t back_drill_figure_width;
    uint32_t back_drill_figure_height;

    Figure back_drill_figure;

    std::string back_drill_characters;

    // counterdrill

    int32_t counter_drill_diameter;
    int32_t counter_drill_positivetolerance;
    int32_t counter_drill_negativetolerance;

    int32_t counterangle;

    std::vector<Pad> genericLayers;

    time_t dateTime1;

    std::string username;

    time_t dateTime2;
    time_t dateTime3;
    time_t dateTime4;
    time_t dateTime5;
    time_t dateTime6;

    std::string programAndVersion;
};



[[maybe_unused]]
static std::string to_string(const PadFile& padFile)
{
    std::string str;

    str += "PadFile:" + newLine();
    str += indent(1) + "swVersion = " + padFile.swVersion + newLine();
    str += indent(1) + "accuracy  = " + std::to_string(padFile.accuracy) + newLine();
    str += indent(1) + "unit      = " + to_string(padFile.unit) + newLine();

    // @todo idxStrPairLst is still missing

    str += indent(1) + "strIdxPadName       = " + std::to_string(padFile.strIdxPadName) + " (" + padFile.getPadName() + ")" + newLine();
    str += indent(1) + "idxUnknown          = " + std::to_string(padFile.idxUnknown) + newLine();
    str += indent(1) + "strIdxDrillToolSize = " + std::to_string(padFile.strIdxDrillToolSize) + " (" + padFile.getDrillToolSize() + ")" + newLine();

    str += indent(1) + "drillmethod     = " + to_string(padFile.drillmethod) + newLine();
    str += indent(1) + "holeType        = " + to_string(padFile.holeType) + newLine();
    str += indent(1) + "staggeredDrills = " + std::to_string(padFile.staggeredDrills) + newLine();
    str += indent(1) + "plated          = " + std::to_string(padFile.plated) + newLine();

    str += indent(1) + "not_suppress_nc_internal_pads = " + std::to_string(padFile.not_suppress_nc_internal_pads) + newLine();
    str += indent(1) + "isPolyVia       = " + std::to_string(padFile.isPolyVia) + newLine();

    str += indent(1) + "padstackusage   = " + to_string(padFile.padstackusage) + newLine();
    str += indent(1) + "drill_rows      = " + std::to_string(padFile.drill_rows) + newLine();
    str += indent(1) + "drill_columns   = " + std::to_string(padFile.drill_columns) + newLine();

    str += indent(1) + "lock_layer_span = " + std::to_string(padFile.lock_layer_span) + newLine();
    str += indent(1) + "offsetX         = " + std::to_string(padFile.offsetX) + newLine();
    str += indent(1) + "offsetY         = " + std::to_string(padFile.offsetY) + newLine();

    str += indent(1) + "clearance_columns = " + std::to_string(padFile.clearance_columns) + newLine();
    str += indent(1) + "clearance_rows    = " + std::to_string(padFile.clearance_rows) + newLine();

    str += indent(1) + "finished_size     = " + std::to_string(padFile.finished_size) + newLine();

    str += indent(1) + "positivetolerance = " + std::to_string(padFile.positivetolerance) + newLine();
    str += indent(1) + "negativetolerance = " + std::to_string(padFile.negativetolerance) + newLine();

    str += indent(1) + "slothole_width  = " + std::to_string(padFile.slothole_width) + newLine();
    str += indent(1) + "slothole_height = " + std::to_string(padFile.slothole_height) + newLine();
    str += indent(1) + "slothole_positivetolerancey = " + std::to_string(padFile.slothole_positivetolerancey) + newLine();
    str += indent(1) + "slothole_negativetolerancey = " + std::to_string(padFile.slothole_negativetolerancey) + newLine();

    str += indent(1) + "width             = " + std::to_string(padFile.width) + newLine();
    str += indent(1) + "height            = " + std::to_string(padFile.height) + newLine();

    str += indent(1) + "figure            = " + to_string(padFile.figure) + newLine();
    str += indent(1) + "characters        = " + padFile.characters + newLine();

    str += indent(1) + "back_drill_figure_width  = " + std::to_string(padFile.back_drill_figure_width) + newLine();
    str += indent(1) + "back_drill_figure_height = " + std::to_string(padFile.back_drill_figure_height) + newLine();

    str += indent(1) + "back_drill_figure        = " + to_string(padFile.back_drill_figure) + newLine();
    str += indent(1) + "back_drill_characters    = " + padFile.back_drill_characters + newLine();

    str += indent(1) + "counter_drill_diameter          = " + std::to_string(padFile.counter_drill_diameter) + newLine();
    str += indent(1) + "counter_drill_positivetolerance = " + std::to_string(padFile.counter_drill_positivetolerance) + newLine();
    str += indent(1) + "counter_drill_negativetolerance = " + std::to_string(padFile.counter_drill_negativetolerance) + newLine();

    str += indent(1) + "counterangle         = " + std::to_string(padFile.counterangle) + newLine();

    // @todo Generic Layer information is still missing
    str += indent(1) + "genericLayers:" + newLine();
    for(size_t i = 0u; i < padFile.genericLayers.size(); ++i)
    {
        str += indent(std::to_string(i) + ": " + to_string(padFile.genericLayers[i]), 2);
    }

    str += indent(1) + "dateTime1         = " + DateTimeToStr(padFile.dateTime1) + newLine();

    str += indent(1) + "username          = " + padFile.username + newLine();

    str += indent(1) + "dateTime2         = " + DateTimeToStr(padFile.dateTime2) + newLine();
    str += indent(1) + "dateTime3         = " + DateTimeToStr(padFile.dateTime3) + newLine();
    str += indent(1) + "dateTime4         = " + DateTimeToStr(padFile.dateTime4) + newLine();
    str += indent(1) + "dateTime5         = " + DateTimeToStr(padFile.dateTime5) + newLine();
    str += indent(1) + "dateTime6         = " + DateTimeToStr(padFile.dateTime6) + newLine();

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& os, const PadFile& padFile)
{
    os << to_string(padFile);

    return os;
}


#endif // PADFILE_HPP
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

    std::string swVersion;

    uint16_t accuracy;
    Units unit;

    // @todo Figure out how the structure works and replace the vector
    //       with a map with indicies of std::any or std::string
    std::vector<std::pair<int, std::string>> idxStrPairLst;

    // @todo Implement as getDrillToolSizeStr() method as this is
    //       actually provided by idxStrPairLst and strIdxDrillToolSize
    std::string drilltoolsize;

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


#endif // PADFILE_HPP
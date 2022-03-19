#ifndef LAYERSTUFF_HPP
#define LAYERSTUFF_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>


enum class Type
{
    REGULAR_PAD,
    THERMAL_PAD,
    ANTIPAD_PAD,
    KEEPOUT,
    USER_MASK,
    UNKNOWN // @todo remove
};


// @todo shift operator
[[maybe_unused]]
static std::string to_string(const Type& type)
{
    std::string str;

    switch(type)
    {
        case Type::REGULAR_PAD: str = "REGULAR_PAD"; break;
        case Type::THERMAL_PAD: str = "THERMAL_PAD"; break;
        case Type::ANTIPAD_PAD: str = "ANTIPAD_PAD"; break;
        case Type::KEEPOUT:     str = "KEEPOUT";     break;
        case Type::USER_MASK:   str = "USER_MASK";   break;
        case Type::UNKNOWN:     str = "UNKNOWN";     break; // @todo remove
        default:
            std::string errorMsg = "Type " + std::to_string(static_cast<size_t>(type))
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return str;
}


// @todo Add BACKDRILL_START and BACKDRILL_CLEARANCE. See BBVia Design Layers
enum class Layer
{
    BEGIN_LAYER,
    DEFAULT_INTERNAL,
    END_LAYER,
    ADJACENT_KEEPOUT,
    TOP_SOLDER_MASK_PAD,
    BOTTOM_SOLDER_MASK_PAD,
    TOP_PASTE_MASK_PAD,
    BOTTOM_PASTE_MASK_PAD,
    TOP_FILM_MASK_PAD,
    BOTTOM_FILM_MASK_PAD,
    TOP_COVERLAY_PAD,
    BOTTOM_COVERLAY_PAD,
    BACKDRILL_SOLDERMASK,
    BACKDRILL_START,
    BACKDRILL_CLEARANCE,
    USR_STR,
    UNKNOWN // @todo remove
};


// @todo implement shift operator
[[maybe_unused]]
static std::string to_string(const Layer& layer)
{
    std::string str;

    switch(layer)
    {
        case Layer::BEGIN_LAYER:            str = "BEGIN_LAYER";            break;
        case Layer::DEFAULT_INTERNAL:       str = "DEFAULT_INTERNAL";       break;
        case Layer::END_LAYER:              str = "END_LAYER";              break;
        case Layer::ADJACENT_KEEPOUT:       str = "ADJACENT_KEEPOUT";       break;
        case Layer::TOP_SOLDER_MASK_PAD:    str = "TOP_SOLDER_MASK_PAD";    break;
        case Layer::BOTTOM_SOLDER_MASK_PAD: str = "BOTTOM_SOLDER_MASK_PAD"; break;
        case Layer::TOP_PASTE_MASK_PAD:     str = "TOP_PASTE_MASK_PAD";     break;
        case Layer::BOTTOM_PASTE_MASK_PAD:  str = "BOTTOM_PASTE_MASK_PAD";  break;
        case Layer::TOP_FILM_MASK_PAD:      str = "TOP_FILM_MASK_PAD";      break;
        case Layer::BOTTOM_FILM_MASK_PAD:   str = "BOTTOM_FILM_MASK_PAD";   break;
        case Layer::TOP_COVERLAY_PAD:       str = "TOP_COVERLAY_PAD";       break;
        case Layer::BOTTOM_COVERLAY_PAD:    str = "BOTTOM_COVERLAY_PAD";    break;
        case Layer::BACKDRILL_SOLDERMASK:   str = "BACKDRILL_SOLDERMASK";   break;
        case Layer::BACKDRILL_START:        str = "BACKDRILL_START";        break;
        case Layer::BACKDRILL_CLEARANCE:    str = "BACKDRILL_CLEARANCE";    break;
        case Layer::USR_STR:                str = "USR_STR";                break;
        case Layer::UNKNOWN:                str = "UNKNOWN";                break; // @todo remove
        default:
            std::string errorMsg = "Layer " + std::to_string(static_cast<size_t>(layer))
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return str;
}


struct padTypeLayer
{
    Type  type;
    Layer layer;
};


extern const std::vector<padTypeLayer> layerLst1;
extern const std::vector<padTypeLayer> layerLst2;


#endif // LAYERSTUFF_HPP
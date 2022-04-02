#ifndef LAYERSTUFF_HPP
#define LAYERSTUFF_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <magic_enum.hpp>

#include "General.hpp"


enum class Type
{
    REGULAR_PAD,
    THERMAL_PAD,
    ANTIPAD_PAD,
    KEEPOUT,
    USER_MASK,
    UNKNOWN // @todo remove
};


[[maybe_unused]]
static constexpr Type ToType(uint32_t aVal)
{
    return ToEnum<Type, decltype(aVal)>(aVal);
}


[[maybe_unused]]
static std::string to_string(const Type& aVal)
{
    return std::string{magic_enum::enum_name<decltype(aVal)>(aVal)};
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const Type& aVal)
{
    aOs << to_string(aVal);
    return aOs;
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
    USER_STR,
    UNKNOWN // @todo remove
};


[[maybe_unused]]
static constexpr Layer ToLayer(uint32_t aVal)
{
    return ToEnum<Layer, decltype(aVal)>(aVal);
}


[[maybe_unused]]
static std::string to_string(const Layer& aVal)
{
    return std::string{magic_enum::enum_name<decltype(aVal)>(aVal)};
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const Layer& aVal)
{
    aOs << to_string(aVal);
    return aOs;
}


struct PadTypeLayer
{
    Type  type;
    Layer layer;
};


[[maybe_unused]]
static std::string to_string(const PadTypeLayer& aObj)
{
    std::string str;

    str += std::string(nameof::nameof_type<decltype(aObj)>()) + ":" + newLine();
    str += indent(1) + "type  = " + to_string(aObj.type) + newLine();
    str += indent(1) + "layer = " + to_string(aObj.layer) + newLine();

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const PadTypeLayer& aObj)
{
    aOs << to_string(aObj);
    return aOs;
}


extern const std::vector<PadTypeLayer> layerLst1;
extern const std::vector<PadTypeLayer> layerLst2;


#endif // LAYERSTUFF_HPP
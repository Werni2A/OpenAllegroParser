#ifndef FIGURE_HPP
#define FIGURE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include <magic_enum.hpp>

#include "General.hpp"


enum class Figure
{
    NONE                =  0,
    CIRCLE              =  2,
    OCTAGON             =  3,
    CROSS               =  4,
    SQUARE              =  5,
    RECTANGLE           =  6,
    DIAMOND             =  7,
    OBLONGX             = 11, // Just named `OBLONG` in *.pxml
    OBLONGY             = 12, // Just named `OBLONG` in *.pxml
    HEXAGONX            = 15,
    HEXAGONY            = 16,
    TRIANGLE            = 18,
    SHAPE_SYMBOL        = 22,
    FLASH               = 23,
    DONUT               = 25,
    ROUNDED_RECTANGLE   = 27,
    CHAMFERED_RECTANGLE = 28,
    NSIDED_POLYGON      = 30
};


[[maybe_unused]]
static constexpr Figure ToFigure(uint32_t aVal)
{
    return ToEnum<Figure, decltype(aVal)>(aVal);
}


// If `aSimplifyOblong` is set, `OBLONGX` and `OBLONGY` will be returned as `OBLONG`.
[[maybe_unused]]
static std::string to_string(const Figure& aVal, bool aSimplifyOblong = false)
{
    std::string str = std::string{magic_enum::enum_name<decltype(aVal)>(aVal)};

    if(aSimplifyOblong)
    {
        switch(aVal)
        {
            case Figure::OBLONGX:
            case Figure::OBLONGY:
                str = "OBLONG";
                break;

            default:
                break;
        }
    }

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const Figure& aVal)
{
    aOs << to_string(aVal);
    return aOs;
}


#endif // FIGURE_HPP
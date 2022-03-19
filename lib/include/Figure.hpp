#ifndef FIGURE_HPP
#define FIGURE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


enum class Figure
{
    NONE                =  0,
    CIRCLE              =  2,
    OCTAGON             =  3,
    CROSS               =  4,
    SQUARE              =  5,
    RECTANGLE           =  6,
    DIAMOND             =  7,
    // OBLONG              = 11,
    OBLONGX             = 11,
    OBLONGY             = 12,
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
static Figure ToFigure(uint32_t val)
{
    Figure figure;

    switch(val)
    {
        case  0: figure = Figure::NONE;                break;
        case  2: figure = Figure::CIRCLE;              break;
        case  3: figure = Figure::OCTAGON;             break;
        case  4: figure = Figure::CROSS;               break;
        case  5: figure = Figure::SQUARE;              break;
        case  6: figure = Figure::RECTANGLE;           break;
        case  7: figure = Figure::DIAMOND;             break;
        case 11: figure = Figure::OBLONGX;             break;
        case 12: figure = Figure::OBLONGY;             break;
        case 15: figure = Figure::HEXAGONX;            break;
        case 16: figure = Figure::HEXAGONY;            break;
        case 18: figure = Figure::TRIANGLE;            break;
        case 22: figure = Figure::SHAPE_SYMBOL;        break;
        case 23: figure = Figure::FLASH;               break;
        case 25: figure = Figure::DONUT;               break;
        case 27: figure = Figure::ROUNDED_RECTANGLE;   break;
        case 28: figure = Figure::CHAMFERED_RECTANGLE; break;
        case 30: figure = Figure::NSIDED_POLYGON;      break;
        default:
            std::string errorMsg = "Figure with value " + std::to_string(val)
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return figure;
}


[[maybe_unused]]
static std::string to_string(const Figure& figure)
{
    std::string str;

    switch(figure)
    {
        case Figure::NONE:                str = "NONE";                break;
        case Figure::CIRCLE:              str = "CIRCLE";              break;
        case Figure::OCTAGON:             str = "OCTAGON";             break;
        case Figure::CROSS:               str = "CROSS";               break;
        case Figure::SQUARE:              str = "SQUARE";              break;
        case Figure::RECTANGLE:           str = "RECTANGLE";           break;
        case Figure::DIAMOND:             str = "DIAMOND";             break;
        case Figure::OBLONGX:             str = "OBLONGX";             break;
        case Figure::OBLONGY:             str = "OBLONGY";             break;
        case Figure::HEXAGONX:            str = "HEXAGONX";            break;
        case Figure::HEXAGONY:            str = "HEXAGONY";            break;
        case Figure::TRIANGLE:            str = "TRIANGLE";            break;
        case Figure::SHAPE_SYMBOL:        str = "SHAPE_SYMBOL";        break;
        case Figure::FLASH:               str = "FLASH";               break;
        case Figure::DONUT:               str = "DONUT";               break;
        case Figure::ROUNDED_RECTANGLE:   str = "ROUNDED_RECTANGLE";   break;
        case Figure::CHAMFERED_RECTANGLE: str = "CHAMFERED_RECTANGLE"; break;
        case Figure::NSIDED_POLYGON:      str = "NSIDED_POLYGON";      break;
        default:
            std::string errorMsg = "Figure " + std::to_string(static_cast<size_t>(figure))
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& os, const Figure& figure)
{
    os << to_string(figure) << std::endl;
    return os;
}


#endif // FIGURE_HPP
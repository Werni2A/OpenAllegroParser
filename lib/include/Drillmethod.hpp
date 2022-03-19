#ifndef DRILLMETHOD_HPP
#define DRILLMETHOD_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


enum class Drillmethod
{
    NONE   = 0,
    LASER  = 1,
    PLASMA = 2,
    PUNCH  = 3,
    OTHER  = 4,
    ETCH   = 5, // Wet/dry etching
    PHOTO  = 6, // Photo imaging
    COND   = 7, // Conductive ink formation
    DUAL   = 8
};


[[maybe_unused]]
static Drillmethod ToDrillmethod(uint32_t val)
{
    Drillmethod drillmethod;

    switch(val)
    {
        case 0: drillmethod = Drillmethod::NONE;   break;
        case 1: drillmethod = Drillmethod::LASER;  break;
        case 2: drillmethod = Drillmethod::PLASMA; break;
        case 3: drillmethod = Drillmethod::PUNCH;  break;
        case 4: drillmethod = Drillmethod::OTHER;  break;
        case 5: drillmethod = Drillmethod::ETCH;   break;
        case 6: drillmethod = Drillmethod::PHOTO;  break;
        case 7: drillmethod = Drillmethod::COND;   break;
        case 8: drillmethod = Drillmethod::DUAL;   break;
        default:
            std::string errorMsg = "Drillmethod with value " + std::to_string(val)
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return drillmethod;
}


[[maybe_unused]]
static std::string to_string(const Drillmethod& drillmethod)
{
    std::string str;

    switch(drillmethod)
    {
        case Drillmethod::NONE:   str = "NONE";   break;
        case Drillmethod::LASER:  str = "LASER";  break;
        case Drillmethod::PLASMA: str = "PLASMA"; break;
        case Drillmethod::PUNCH:  str = "PUNCH";  break;
        case Drillmethod::OTHER:  str = "OTHER";  break;
        case Drillmethod::ETCH:   str = "ETCH";   break;
        case Drillmethod::PHOTO:  str = "PHOTO";  break;
        case Drillmethod::COND:   str = "COND";   break;
        case Drillmethod::DUAL:   str = "DUAL";   break;
        default:
            std::string errorMsg = "Drillmethod " + std::to_string(static_cast<size_t>(drillmethod))
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& os, const Drillmethod& drillmethod)
{
    os << to_string(drillmethod) << std::endl;
    return os;
}


#endif // DRILLMETHOD_HPP
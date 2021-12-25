#ifndef UNITS_HPP
#define UNITS_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


enum class Units
{
    mils = 1,
    inch = 2,
    mm   = 3, // Millimeter
    cm   = 4, // Centimeter
    um   = 5  // Micron/Micrometer
};


[[maybe_unused]]
static Units ToUnits(uint32_t val)
{
    Units units;

    switch(val)
    {
        case 1: units = Units::mils; break;
        case 2: units = Units::inch; break;
        case 3: units = Units::mm;   break;
        case 4: units = Units::cm;   break;
        case 5: units = Units::um;   break;
        default:
            std::string errorMsg = "Units with value " + std::to_string(val)
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return units;
}


[[maybe_unused]]
static std::string to_string(const Units& units)
{
    std::string str;

    switch(units)
    {
        case Units::mils: str = "mils"; break;
        case Units::inch: str = "inch"; break;
        case Units::mm:   str = "mm";   break;
        case Units::cm:   str = "cm";   break;
        case Units::um:   str = "um";   break;
        default:
            std::string errorMsg = "Units " + std::to_string(static_cast<size_t>(units))
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& os, const Units& units)
{
    os << to_string(units) << std::endl;
    return os;
}


#endif // UNITS_HPP
#ifndef UNITS_HPP
#define UNITS_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include <magic_enum.hpp>

#include "General.hpp"


enum class Units
{
    mils = 1,
    inch = 2,
    mm   = 3, // Millimeter
    cm   = 4, // Centimeter
    um   = 5  // Micron/Micrometer
};


[[maybe_unused]]
static constexpr Units ToUnits(uint32_t aVal)
{
    return ToEnum<Units, decltype(aVal)>(aVal);
}


[[maybe_unused]]
static std::string to_string(const Units& aVal)
{
    return std::string{magic_enum::enum_name<decltype(aVal)>(aVal)};
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const Units& aVal)
{
    aOs << to_string(aVal);
    return aOs;
}


#endif // UNITS_HPP
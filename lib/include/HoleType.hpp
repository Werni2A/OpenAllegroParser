#ifndef HOLETYPE_HPP
#define HOLETYPE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include <magic_enum.hpp>

#include "General.hpp"


enum class HoleType
{
    NONE      = 0,
    CIRCLE    = 1,
    SQUARE    = 2,
    OVAL_SLOT = 3,
    RECT_SLOT = 4
};


[[maybe_unused]]
static constexpr HoleType ToHoleType(uint32_t aVal)
{
    return ToEnum<HoleType, decltype(aVal)>(aVal);
}


[[maybe_unused]]
static std::string to_string(const HoleType& aVal)
{
    return std::string{magic_enum::enum_name<decltype(aVal)>(aVal)};
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const HoleType& aVal)
{
    aOs << to_string(aVal);
    return aOs;
}


#endif // HOLETYPE_HPP
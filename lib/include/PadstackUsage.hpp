#ifndef PADSTACKUSAGE_HPP
#define PADSTACKUSAGE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include <magic_enum.hpp>

#include "General.hpp"


enum class PadstackUsage
{
    THRU_PIN    =  1,
    SMD_PIN     =  2,
    VIA         =  3,
    BBVIA       =  4,
    MICROVIA    =  5,
    DIE_PAD     =  6,
    BOND_FINGER =  7,
    FIDUCIAL    =  8,
    SLOT        =  9,
    MECH_HOLE   = 10,
    TOOL_HOLE   = 11,
    MOUNT_HOLE  = 12
};


[[maybe_unused]]
static constexpr PadstackUsage ToPadstackUsage(uint32_t aVal)
{
    return ToEnum<PadstackUsage, decltype(aVal)>(aVal);
}


[[maybe_unused]]
static std::string to_string(const PadstackUsage& aVal)
{
    return std::string{magic_enum::enum_name<decltype(aVal)>(aVal)};
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const PadstackUsage& aVal)
{
    aOs << to_string(aVal);
    return aOs;
}


#endif // PADSTACKUSAGE_HPP
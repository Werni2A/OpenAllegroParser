#ifndef PADSTACKUSAGE_HPP
#define PADSTACKUSAGE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>

#include <magic_enum.hpp>

#include "General.hpp"


// @todo It's strange that the suffix is always b10.
//       Probably a bit field where the lower 2 bits
//       are something different?
enum class PadstackUsage
{
                      // First two bits are always b10, therefore discard them here -> bit field
    THRU_PIN    =  6, //  1,
    SMD_PIN     = 10, //  2,
    VIA         = 14, //  3,
    BBVIA       = 18, //  4,
    MICROVIA    = 22, //  5,
    DIE_PAD     = 26, //  6,
    BOND_FINGER = 30, //  7,
    FIDUCIAL    = 34, //  8,
    SLOT        = 38, //  9,
    MECH_HOLE   = 42, // 10,
    TOOL_HOLE   = 46, // 11,
    MOUNT_HOLE  = 50  // 12
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
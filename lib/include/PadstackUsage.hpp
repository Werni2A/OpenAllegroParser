#ifndef PADSTACKUSAGE_HPP
#define PADSTACKUSAGE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


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
static PadstackUsage ToPadstackUsage(uint8_t val)
{
    PadstackUsage padstackUsage;

    switch(val)
    {
        case  6 /* 1*/: padstackUsage = PadstackUsage::THRU_PIN;    break;
        case 10 /* 2*/: padstackUsage = PadstackUsage::SMD_PIN;     break;
        case 14 /* 3*/: padstackUsage = PadstackUsage::VIA;         break;
        case 18 /* 4*/: padstackUsage = PadstackUsage::BBVIA;       break;
        case 22 /* 5*/: padstackUsage = PadstackUsage::MICROVIA;    break;
        case 26 /* 6*/: padstackUsage = PadstackUsage::DIE_PAD;     break;
        case 30 /* 7*/: padstackUsage = PadstackUsage::BOND_FINGER; break;
        case 34 /* 8*/: padstackUsage = PadstackUsage::FIDUCIAL;    break;
        case 38 /* 9*/: padstackUsage = PadstackUsage::SLOT;        break;
        case 42 /*10*/: padstackUsage = PadstackUsage::MECH_HOLE;   break;
        case 46 /*11*/: padstackUsage = PadstackUsage::TOOL_HOLE;   break;
        case 50 /*12*/: padstackUsage = PadstackUsage::MOUNT_HOLE;  break;
        default:
            std::string errorMsg = "PadstackUsage with value " + std::to_string(val)
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return padstackUsage;
}


[[maybe_unused]]
static std::string to_string(const PadstackUsage& padstackUsage)
{
    std::string str;

    switch(padstackUsage)
    {
        case PadstackUsage::THRU_PIN:    str = "THRU_PIN";    break;
        case PadstackUsage::SMD_PIN:     str = "SMD_PIN";     break;
        case PadstackUsage::VIA:         str = "VIA";         break;
        case PadstackUsage::BBVIA:       str = "BBVIA";       break;
        case PadstackUsage::MICROVIA:    str = "MICROVIA";    break;
        case PadstackUsage::DIE_PAD:     str = "DIE_PAD";     break;
        case PadstackUsage::BOND_FINGER: str = "BOND_FINGER"; break;
        case PadstackUsage::FIDUCIAL:    str = "FIDUCIAL";    break;
        case PadstackUsage::SLOT:        str = "SLOT";        break;
        case PadstackUsage::MECH_HOLE:   str = "MECH_HOLE";   break;
        case PadstackUsage::TOOL_HOLE:   str = "TOOL_HOLE";   break;
        case PadstackUsage::MOUNT_HOLE:  str = "MOUNT_HOLE";  break;
        default:
            std::string errorMsg = "PadstackUsage " + std::to_string(static_cast<size_t>(padstackUsage))
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& os, const PadstackUsage& padstackUsage)
{
    os << to_string(padstackUsage) << std::endl;
    return os;
}


#endif // PADSTACKUSAGE_HPP
#ifndef PADSTACKUSAGE_HPP
#define PADSTACKUSAGE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


// @todo Strange padding to 3 bits
//       is there some meaning of the lower
//       few bits? Probably a bit field where the lower 2 bits are something different
enum class PadstackUsage
{
    THRU_PIN    =  1, //  6,
    SMD_PIN     =  2, // 10,
    VIA         =  3, // 14,
    BBVIA       =  4, // 18,
    MICROVIA    =  5, // 22,
    DIE_PAD     =  6, // 26,
    BOND_FINGER =  7, // 30,
    FIDUCIAL    =  8, // 34,
    SLOT        =  9, // 38,
    MECH_HOLE   = 10, // 42,
    TOOL_HOLE   = 11, // 46,
    MOUNT_HOLE  = 12  // 50
};


[[maybe_unused]]
static PadstackUsage ToPadstackUsage(uint32_t val)
{
    PadstackUsage padstackUsage;

    switch(val)
    {
        case  1: padstackUsage = PadstackUsage::THRU_PIN;    break;
        case  2: padstackUsage = PadstackUsage::SMD_PIN;     break;
        case  3: padstackUsage = PadstackUsage::VIA;         break;
        case  4: padstackUsage = PadstackUsage::BBVIA;       break;
        case  5: padstackUsage = PadstackUsage::MICROVIA;    break;
        case  6: padstackUsage = PadstackUsage::DIE_PAD;     break;
        case  7: padstackUsage = PadstackUsage::BOND_FINGER; break;
        case  8: padstackUsage = PadstackUsage::FIDUCIAL;    break;
        case  9: padstackUsage = PadstackUsage::SLOT;        break;
        case 10: padstackUsage = PadstackUsage::MECH_HOLE;   break;
        case 11: padstackUsage = PadstackUsage::TOOL_HOLE;   break;
        case 12: padstackUsage = PadstackUsage::MOUNT_HOLE;  break;
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
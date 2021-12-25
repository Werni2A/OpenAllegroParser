#ifndef HOLETYPE_HPP
#define HOLETYPE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


enum class HoleType
{
    NONE      =  0, // @todo needs verification
    CIRCLE    = 33, // @todo needs verification
    // SQUARE   = , // @todo figure out the value
    OVAL_SLOT = 35,
    RECT_SLOT = 36
};


[[maybe_unused]]
static HoleType ToHoleType(uint32_t val)
{
    HoleType holeType;

    switch(val)
    {
        case  0: holeType = HoleType::NONE;      break;
        case 33: holeType = HoleType::CIRCLE;    break;
        case 35: holeType = HoleType::OVAL_SLOT; break;
        case 36: holeType = HoleType::RECT_SLOT; break;
        default:
            std::string errorMsg = "HoleType with value " + std::to_string(val)
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return holeType;
}


[[maybe_unused]]
static std::string to_string(const HoleType& holeType)
{
    std::string str;

    switch(holeType)
    {
        case HoleType::NONE:      str = "NONE";      break;
        case HoleType::CIRCLE:    str = "CIRCLE";    break;
        case HoleType::OVAL_SLOT: str = "OVAL_SLOT"; break;
        case HoleType::RECT_SLOT: str = "RECT_SLOT"; break;
        default:
            std::string errorMsg = "HoleType " + std::to_string(static_cast<size_t>(holeType))
                                 + " is not implemented!";
            throw std::invalid_argument(errorMsg);
            break;
    }

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& os, const HoleType& holeType)
{
    os << to_string(holeType) << std::endl;
    return os;
}


#endif // HOLETYPE_HPP
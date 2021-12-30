#ifndef HOLETYPE_HPP
#define HOLETYPE_HPP


#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>


enum class HoleType
{
    NONE      = 0,
    CIRCLE    = 1,
    SQUARE    = 2,
    OVAL_SLOT = 3,
    RECT_SLOT = 4
};


[[maybe_unused]]
static HoleType ToHoleType(uint32_t val)
{
    HoleType holeType;

    switch(val)
    {
        case 0: holeType = HoleType::NONE;      break;
        case 1: holeType = HoleType::CIRCLE;    break;
        case 2: holeType = HoleType::SQUARE;    break;
        case 3: holeType = HoleType::OVAL_SLOT; break;
        case 4: holeType = HoleType::RECT_SLOT; break;
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
        case HoleType::SQUARE:    str = "SQUARE";    break;
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
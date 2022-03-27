
#ifndef SYMBOL_HPP
#define SYMBOL_HPP


#include <cstdint>
#include <ostream>
#include <string>

#include <nameof.hpp>


class Symbol
{
public:

    uint32_t width;
    uint32_t height;

    Figure figure;

    std::string characters;
};


[[maybe_unused]]
static std::string to_string(const Symbol& aObj)
{
    std::string str;

    str += std::string(nameof::nameof_type<decltype(aObj)>()) + ":" + newLine();
    str += indent(1) + "width      = " + std::to_string(aObj.width) + newLine();
    str += indent(1) + "height     = " + std::to_string(aObj.height) + newLine();
    str += indent(1) + "figure     = " + to_string(aObj.figure) + newLine();
    str += indent(1) + "characters = " + aObj.characters + newLine();

    return str;
}


[[maybe_unused]]
static std::ostream& operator<<(std::ostream& aOs, const Symbol& aVal)
{
    aOs << to_string(aVal);

    return aOs;
}


#endif // SYMBOL_HPP
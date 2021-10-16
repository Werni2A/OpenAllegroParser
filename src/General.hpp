#ifndef GENERAL_H
#define GENERAL_H


#include <cstdint>
#include <iostream>
#include <string>


/**
 * @brief Version of the file format.
 * @warning This is not an official version but was introduced
 *          by myself as I don't know how or where the acutal
 *          version number is stored.
 */
enum class FileFormatVersion
{
    Unknown,
    A, // Oldest version
    B,
    C  // Latest Version
};


enum class FileType
{
    brd, // Board database
    mdd, // Module definition
    dra, // Drawing
    psm, // Package symbol
    ssm, // Shape symbol
    fsm, // Flash symbol
    osm, // Format symbol
    bsm, // Mechanical symbol
    pad  // Padstack
};


template<typename T>
[[maybe_unused]] static std::string ToHex(T val, size_t digits)
{
    // @todo Use fmt lib!
    char hex[16];
    std::string format = "%0" + std::to_string(digits) + "x";
    std::sprintf(hex, format.c_str(), static_cast<unsigned int>(val));
    return std::string(hex);
}


// [[maybe_unused]]
// void expectStr(const std::string& str, const std::string& ref)
// {
//     if(str != ref)
//     {
//         throw std::runtime_error("Exptected string '" + ref + "' but got '" + str + "'!");
//     }
// }


#endif // GENERAL_H
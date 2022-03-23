#ifndef GENERAL_H
#define GENERAL_H


#include <algorithm>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>


/**
 * @brief Version of the file format.
 */
enum class FileFormatVersion
{
    Unknown,
    V17_4_S012 // 10/18/2020 - pad3898010/18
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


[[maybe_unused]]
static void expectStr(const std::string& str, const std::string& ref)
{
    if(str != ref)
    {
        throw std::runtime_error("Exptected string '" + ref + "' but got '" + str + "'!");
    }
}


[[maybe_unused]]
static std::string DateTimeToStr(const time_t& unixts)
{
    return std::string(std::ctime(&unixts));
}


[[maybe_unused]]
static std::time_t ToTime(uint32_t aTime)
{
    std::time_t time = static_cast<time_t>(aTime);

    // Cadence Systems was founded in 1988, therefore all files
    // can not date back to earlier years.
    std::tm tm{}; // Zero initialise
    tm.tm_year  = 1988 - 1900; // 1960

    std::time_t earliestTime = std::mktime(&tm);
    std::time_t latestTime   = std::time(nullptr);

    if(time < earliestTime || time > latestTime)
    {
        throw std::runtime_error("Time musst be in between "
             + DateTimeToStr(earliestTime) + " <= " + DateTimeToStr(time) + " <= " + DateTimeToStr(latestTime) + "!");
    }

    return time;
}


/**
 * @brief Convert fix point coordinate to floating point.
 * @note Allegro stores floating point values as fixed point value
 *       instead of the actual floating point representation.
 *
 * @param point Fix point coordiante.
 * @return double Floating point coordinate.
 */
template<typename T>
static double ToFP(T point)
{
    return static_cast<double>(point) / 100.0;
}


[[maybe_unused]]
static std::string newLine()
{
    return "\n";
}


[[maybe_unused]]
static std::string indent(std::string str, size_t level)
{
    const std::string indent = "  ";
    const std::string delimiter = newLine();

    std::vector<std::string> lines;

    size_t pos = 0;
    std::string token;
    while ((pos = str.find(delimiter)) != std::string::npos)
    {
        token = str.substr(0, pos);
        lines.push_back(std::move(token) + newLine());
        str.erase(0, pos + delimiter.length());
    }

    lines.push_back(std::move(str));

    std::string indentedStr;
    for(auto&& line : lines)
    {
        if(!line.empty())
        {
            for(size_t i = 0u; i < level; ++i)
            {
                indentedStr += indent;
            }

            indentedStr += line;
        }
    }

    return indentedStr;
}


[[maybe_unused]]
static std::string indent(size_t level)
{
    const std::string indent = "  ";

    std::string retIndent;

    for(size_t i = 0u; i < level; ++i)
    {
        retIndent += indent;
    }
    return retIndent;
}


[[maybe_unused]]
static std::string to_lower(const std::string& aStr)
{
    std::string retVal{aStr};

    std::transform(retVal.begin(), retVal.end(), retVal.begin(),
        [] (unsigned char c) { return std::tolower(c); });

    return retVal;
}


#endif // GENERAL_H
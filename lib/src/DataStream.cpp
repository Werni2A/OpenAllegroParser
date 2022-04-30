#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

#include <spdlog/spdlog.h>

#include "../include/DataStream.hpp"
#include "../include/General.hpp"


void DataStream::discardBytes(size_t aLen)
{
    seekg(aLen, std::ios_base::cur);
}


std::vector<uint8_t> DataStream::readBytes(size_t aLen)
{
    std::vector<uint8_t> data;
    data.resize(aLen);

    for(auto& byte : data)
    {
        byte = readUint8();
    }

    return data;
}


void DataStream::padTo4ByteBoundary()
{
    const size_t padLen = (4u - getCurrentOffset() % 4u) % 4u;

    assumeZero(padLen, "Expected 0x00 for padding bytes!");
}


std::string DataStream::readStringZeroTerm()
{
    std::string str;

    const size_t max_chars = 2000u;

    for(size_t i = 0u; i < max_chars; ++i)
    {
        char c = get();

        if(c != '\0')
        {
            str += c;
        }
        else
        {
            break;
        }
    }

    // @todo This check was added during testing to such that the parser fails when trying to
    //       interpret random data as string. Remove this check as soon as the parser works
    //       stable because strings can actually be very long.
    if(str.length() == max_chars)
    {
        throw std::runtime_error("Loop cancled because the string is unexpectedly large. More than "
                                 + std::to_string(max_chars) + " characters!");
    }

    return str;
}


std::string DataStream::readStringLenTerm()
{
    const uint16_t len = readUint16();

    const size_t max_chars = 400u;

    std::string str;

    for(size_t i = 0u; i < len && i < max_chars; ++i)
    {
        char c = get();

        if(c != '\0')
        {
            str += c;
        }
        else
        {
            throw std::runtime_error("Didn't expect null byte within string!");
        }
    }

    // @todo This check was added during testing to such that the parser fails when trying to
    //       interpret random data as string. Remove this check as soon as the parser works
    //       stable because strings can actually be very long.
    if(str.length() == max_chars)
    {
        throw std::runtime_error("Loop cancled because the string is unexpectedly large. More than "
                                 + std::to_string(max_chars) + " characters!");
    }

    return str;
}


std::string DataStream::readStringLenZeroTerm()
{
    const uint16_t len = readUint16();

    const std::string str = readStringZeroTerm();

    if(str.length() != len)
    {
        const std::string msg = fmt::format("String has preceeding"
            " length definition of {} characters but terminates"
            " after {} characters!",
            len, str.length());

        spdlog::error(msg);

        throw std::runtime_error(msg);
    }

    return str;
}


std::string DataStream::readStrZeroTerm4BytePad()
{
    const size_t startOffset = getCurrentOffset();

    const std::string str = readStringZeroTerm();

    const size_t endOffset = getCurrentOffset();

    // Padding to 4 byte boundaries.
    const size_t padLen = (4u - (endOffset - startOffset) % 4u) % 4u;

    assumeZero(padLen, "Expected 0x00 for padding bytes!");

    return str;
}


std::string DataStream::readStrZeroTermBlock(size_t aBlockSize)
{
    const size_t startOffset = getCurrentOffset();

    const std::string str = readStringZeroTerm();

    const size_t stopOffset = getCurrentOffset();

    if(str.length() >= aBlockSize)
    {
        const std::string msg = fmt::format("String with {} Byte is"
            " too long to fit into a block size of {} Byte!", str.length(), aBlockSize);

        spdlog::error(msg);

        throw std::runtime_error(msg);
    }

    const size_t padLen = aBlockSize - (stopOffset - startOffset);

    assumeZero(padLen, "Expected 0x00 for padding bytes!");

    return str;
}


void DataStream::printUnknownData(size_t aLen, const std::string& aComment)
{
    const auto data = readBytes(aLen);

    if(aLen > 0u)
    {
        spdlog::warn(fmt::format("Reading {} Byte: {}\n{}", aLen, aComment, getStrFromData(data)));
    }
}


void DataStream::padRest(size_t aStartOffset, size_t aBlockSize, bool aPadIsZero)
{
    const size_t currOffset = getCurrentOffset();
    const size_t offsetDiff = currOffset - aStartOffset;

    if(offsetDiff > aBlockSize)
    {
        throw std::runtime_error("Already parsed " + std::to_string(offsetDiff)
                                 + " bytes but should have only been "
                                 + std::to_string(aBlockSize) + "!");
    }

    const size_t paddingLen = aBlockSize - offsetDiff;

    if(aPadIsZero)
    {
        assumeZero(paddingLen, "Padding byte is expected to be 0x00!");
    }
    else
    {
        discardBytes(paddingLen);
        // printUnknownData(std::clog, paddingLen, "Padding Bytes");
    }
}


std::ostream& DataStream::printCurrentOffset(std::ostream& aOs)
{
    const size_t offset = getCurrentOffset();
    // @todo improve with fmt lib!
    char buffer[128];
    std::sprintf(buffer, "Offset at 0x%s", ToHex(offset, 8).c_str());
    aOs << std::string(buffer);

    return aOs;
};


std::string DataStream::getStrFromData(const std::vector<uint8_t>& aData)
{
    const unsigned int line_width = 16u;
    const std::string hex_spacing = " ";
    const std::string str_spacing = "";

    std::string preamble;
    std::string line_hex;
    std::string line_str;

    std::string output;

    std::string line;
    for(size_t i = 0u; i < aData.size(); ++i)
    {
        const size_t offset = getCurrentOffset() - aData.size() + i;

        if(i % line_width == 0u)
        {
            preamble = "0x" + ToHex(offset, 8) + ": ";
        }

        char c = static_cast<char>(aData[i]);
        line_hex += ToHex(aData[i], 2);
        line_str += std::isprint(c) ? c : '.';

        if((i + 1) % line_width == 0u)
        {
            output += preamble + line_hex + " | " + line_str + '\n';
            preamble.clear();
            line_hex.clear();
            line_str.clear();
        }
        else if(i == aData.size() - 1)
        {
            for(size_t i = 0u; i < line_width - (aData.size() % line_width); ++i)
            {
                line_hex += "  " + hex_spacing; // 2 spaces for 1 byte
                line_str += " "  + str_spacing; // 1 character for 1 byte
            }

            output += preamble + line_hex + " | " + line_str + '\n';
        }
        else
        {
            line_hex += hex_spacing;
            line_str += str_spacing;
        }
    }

    return output;
}


void DataStream::assumeData(const std::vector<uint8_t>& aExpectedData, const std::string& aComment)
{
    const std::vector<uint8_t> data = readBytes(aExpectedData.size());

    size_t ctr = 0u;

    const auto checkByte = [&ctr, &aExpectedData](uint8_t byte)
    {
        return byte == aExpectedData[ctr++];
    };

    if(!std::all_of(data.cbegin(), data.cend(), checkByte))
    {
        const std::string expectedDataStr = getStrFromData(aExpectedData);
        const std::string actualDataStr   = getStrFromData(data);

        const auto msg = fmt::format("Assumption failed ({} Byte): {}\n"
            "Expected:\n"
            "{}"
            "but got:\n"
            "{}",
            aExpectedData.size(), aComment, expectedDataStr, actualDataStr);

        spdlog::error(msg);

        throw std::runtime_error(msg);
    }
}


void DataStream::assumeZero(size_t aLen, const std::string& aComment)
{
    std::vector<uint8_t> zeros;

    zeros.assign(aLen, 0x00);

    assumeData(zeros, aComment);
}
#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <stdexcept>
#include <string>

#include <nameof.hpp>


template<typename T, typename TVal>
struct InvalidEnumEntry : public std::invalid_argument
{
    InvalidEnumEntry(TVal aVal) :
        std::invalid_argument("Enum `" + std::string(nameof::nameof_type<T>())
            + "` does not implement value " + std::to_string(aVal) + "!")
    { }
};


#endif // EXCEPTION_H
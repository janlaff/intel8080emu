#pragma once

#include <cstdio>
#include <string>
#include <vector>

#include "EnumTypes.h"

template<typename T>
struct Argument {
    constexpr explicit Argument(const T& value)
        : value(value) {}

    const T& Get() {return value;}

    const T& value;
};

template<>
struct Argument<std::string> {
    constexpr explicit Argument(const std::string& value)
        : value(value) {}

    const char* Get() {return value.c_str();}

    const std::string& value;
};

template<typename ... Args>
std::string Format(const std::string& fmt, const Args&... args) {
    int resultSize = std::snprintf(nullptr, 0, fmt.c_str(), Argument<Args>{args}.Get()...);

    std::vector<char> result(resultSize + 1);
    std::snprintf(result.data(), result.size(), fmt.c_str(), Argument<Args>{args}.Get()...);
    result.resize(std::max(result.size(), 1ul) - 1);

    return {result.begin(), result.end()};
}

bool Replace(std::string& str, const std::string& from, const std::string& to);

std::string FormatEnum(Reg8 value);
std::string FormatEnum(Reg16 value);
std::string FormatEnum(JumpCondition value);
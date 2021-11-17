#pragma once

#include <cstdio>
#include <string>
#include <vector>

static std::string currentStringCopy {};

template<typename T>
struct ArgFormatter {
    static const T& Get(const T& value) {
        return value;
    }
};

template<>
struct ArgFormatter<std::string> {
    static const char* Get(const std::string& value) {
        currentStringCopy = value;
        return currentStringCopy.c_str();
    }
};

template<typename ... Args>
std::string Format(const std::string& fmt, const Args&... args) {
    int resultSize = std::snprintf(nullptr, 0, fmt.c_str(), ArgFormatter<Args>::Get(args)...);

    std::vector<char> result(resultSize + 1);
    std::snprintf(result.data(), result.size(), fmt.c_str(), ArgFormatter<Args>::Get(args)...);

    return  {result.begin(), result.end()};
}
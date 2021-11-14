#pragma once

#include <cstdio>
#include <string>
#include <vector>

template<typename T>
struct ArgFormatter {
    static const T& Get(const T& value) {
        return value;
    }
};

template<>
struct ArgFormatter<std::string> {
    static std::string copyOfCurrentArg;

    static const char* Get(const std::string& value) {
        copyOfCurrentArg = value;
        return copyOfCurrentArg.c_str();
    }
};

std::string ArgFormatter<std::string>::copyOfCurrentArg {};

template<typename ... Args>
std::string Format(const std::string& fmt, const Args&... args) {
    int resultSize = std::snprintf(nullptr, 0, fmt.c_str(), ArgFormatter<Args>::Get(args)...);

    std::vector<char> result(resultSize + 1);
    std::snprintf(result.data(), result.size(), fmt.c_str(), ArgFormatter<Args>::Get(args)...);

    return  {result.begin(), result.end()};
}
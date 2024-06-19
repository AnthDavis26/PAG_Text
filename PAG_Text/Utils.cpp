#include "Utils.h"
#include <cctype>
#include <vector>
#include <algorithm>
#include <iterator>

int Utils::CharNumToInt(char ch) {
    return ch - '0';
}

void Utils::Trim(std::string& str) {
    size_t start = 0;

    while (start < str.length() && std::isspace(str[start])) {
        ++start;
    }

    size_t end = str.length();

    while (end > start && std::isspace(str[end - 1])) {
        --end;
    }

    str = str.substr(start, end - start);
}

int Utils::RandomNumber(int min, int max) {
    std::srand((int)std::time(nullptr));
    return std::rand() % max + min;
}

int Utils::ExtractDigitsFromString(const std::string& str) {
    std::string result = "";

    for (const char x : str) {
        if (std::isdigit(x))
            result += x;
    }

    return std::stoi(result);
}

std::string Utils::ToLowercase(const std::string& str) {
    std::string result = "";

    for (const char x : str)
        result += std::tolower(x);

    return result;
}

std::string Utils::ToUppercase(const std::string& str) {
    std::string result = "";

    for (const char x : str)
        result += std::toupper(x);

    return result;
}

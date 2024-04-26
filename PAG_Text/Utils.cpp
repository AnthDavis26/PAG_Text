#include "Utils.h"
#include <cctype>

int Utils::CharNumToInt(char ch) {
    return ch - '0';
}

void Utils::ClearScreen() {
    system("cls"); // Windows console only
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

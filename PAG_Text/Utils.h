#pragma once
#include <string>

class Utils {
    public:
        static int ExtractDigitsFromString(const std::string& str);
        static std::string ToLowercase(const std::string& str);
        static std::string ToUppercase(const std::string& str);
        static int CharNumToInt(char ch);
        static void ClearScreen();
};

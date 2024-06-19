#pragma once
#include <string>
#include <iostream>

class Utils {
    public:
        static int ExtractDigitsFromString(const std::string& str);
        static std::string ToLowercase(const std::string& str);
        static std::string ToUppercase(const std::string& str);
        static int CharNumToInt(char ch);
        static void Trim(std::string&);
        static int RandomNumber(int min, int max);

        template <typename Container, typename T>
        static bool ObjectContains(const Container& container, const T& elem) {
            return std::find(container.begin(), container.end(), elem) != container.end();
        };
};
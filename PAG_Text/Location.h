#pragma once
#include <string>

class Location {
    public:
        Location(std::string name);
        std::string GetName() const;

    private:
        std::string name;
};

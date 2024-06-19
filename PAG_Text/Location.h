#pragma once
#include <string>
#include <functional>

class Location {
    public:
        Location(std::string name);
        const std::string GetName() const;
        std::function<void()> Start = [] {};

    private:
        std::string name;
};

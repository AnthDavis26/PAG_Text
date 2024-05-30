#pragma once
#include <string>
#include <functional>

class Location {
    public:
        Location(std::string name);
        std::string GetName() const;
        std::function<void()> Start = [] {};
        std::unordered_map<int,int>& GetProps();
        void AddProp(int propKey);
        void RemoveProp(int propKey);

    private:
        std::string name;
        std::unordered_map<int,int> props; // {Prop ID, count}
};

#pragma once
#include <unordered_map>
#include <functional>

class InputChecker {
public:
    static bool ChoiceMatchesCommands(const std::unordered_map<char, std::function<void()>>& validCommands);
    static bool IsDefaultCommand();
    static bool PickedYes();
    static bool PickedNo();
    static bool IsCommandEatTrash();
    static void ProcessCustomCommand();
};


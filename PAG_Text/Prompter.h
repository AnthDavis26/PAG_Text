#pragma once
#include <functional>
#include <string>
#include <unordered_set>
#include <iostream>
#include "InputKeys.h"
#include "Navigator.h"
#include "InputChecker.h"

#define CMD std::make_pair

class Prompter {
public:
    static void PromptChoice();
    static void Print(const std::string& text);
    static std::string GetTextCommand();
    static char GetChoice();
    static void PromptChoiceUntil(std::function<bool()> conditionFunction);
    static void PromptUntilYesOrNo();
    static void PromptPressKey();
    static void PromptTextCommand();
    static void ShowDefaultControls();
    static void ShowInvalidChoice();
    static void ShowGameInfo();
    static void ShowPressToPause();
    static void ShowPressToEnterText();
    static void SetTextEntry(std::string);
    static void ResetChoice();
    static void SetChoice(char);
    static void ShowInvalidTextResponse();
    static void ClearScreen();
    static void SceneTitle(std::string title);
    static std::string InputText();

    template<typename... Commands>
    static void PromptUntilValidCommand(Commands... commands) {
        std::unordered_map<char, std::function<void()>> validCommands = { commands... };
        validCommands.insert({ InputKeys::PAUSE, Navigator::GoToPauseMenu });
        validCommands.insert({ InputKeys::TEXT_ENTRY, Prompter::PromptTextCommand });

        do {
            Prompter::PromptChoice();
        } while (!InputChecker::ChoiceMatchesCommands(validCommands));

        if (Prompter::GetChoice() != InputKeys::TEXT_ENTRY) {
            Prompter::ClearScreen();
        } else {
            Prompter::Print("");
        }

        validCommands.find(Prompter::GetChoice())->second();
    }

private:
    static std::string& GetTextCommandRef();
    static char choice;
    static std::string customCommand;
    static bool promptWasTooLong;
    static const std::vector<std::string> invalidTextResponses;
};

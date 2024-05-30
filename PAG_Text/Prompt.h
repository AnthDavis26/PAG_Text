#pragma once
#include <functional>
#include <string>

class Prompt {
	public:
		static void PromptChoiceUntil(std::function<bool()> conditionFunction);
		static void PromptYesOrNo();
		static void PromptPressKey();
		static void CustomPrompt();
		static std::string& GetCustomPrompt();
		static bool PickedYes();
		static bool PickedNo();
		static char& GetChoice();
		static bool PromptMatchesEatTrash(std::string prompt);
		static void ResetChoice();
		static void SetChoice(char);
		static void InvalidCustomPromptResponse();
	private:
		static void ProcessCustomPrompt();
		static char choice;
		static std::string enteredPrompt;
		static bool promptWasTooLong;
};


#pragma once
#include <functional>

class Selector {
	public:
		static void PromptChoiceUntil(std::function<bool()> conditionFunction);
		static void PromptYesOrNo();
		static bool PickedYes();
		static bool PickedNo();
		static char GetChoice();
		static void ResetChoice();
		static void SetChoice(char);
	private:
		static char choice;
};


#pragma once
#include <functional>

class Selector
{
public:
	static char PromptAndGetChoice(std::function<bool()> conditionFunction);
	static char GetChoice();
	static void ResetChoice();
	static void SetChoice(char);
private:
	static char choice;
};


#include "Selector.h"
#include <conio.h>

char Selector::choice = -1;

char Selector::PromptAndGetChoice(std::function<bool()> conditionFunction)
{
	Selector::ResetChoice();

	do {
		Selector::SetChoice(_getch());
	} while (!conditionFunction());

	return Selector::GetChoice();
	
}

char Selector::GetChoice()
{
	return choice;
}

void Selector::ResetChoice()
{
	choice = -1;
}

void Selector::SetChoice(char ch)
{
	choice = ch;
}

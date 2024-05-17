#include "Selector.h"
#include <conio.h>
#include "InputKeys.h"
#include <iostream>

char Selector::choice = -1;

void Selector::PromptChoiceUntil(std::function<bool()> conditionFunction) {
	Selector::ResetChoice();

	do {
		Selector::SetChoice(_getch());
	} while (!conditionFunction());
	
}

void Selector::PromptYesOrNo() {
	std::cout << InputKeys::MENU_CHOICE_YES << ". Yes\t" << InputKeys::MENU_CHOICE_NO << ". No" << std::endl;
	Selector::PromptChoiceUntil([]() {
		return Selector::PickedYes() || Selector::PickedNo();
	});
}

bool Selector::PickedYes() {
	return Selector::GetChoice() == InputKeys::MENU_CHOICE_YES;
}

bool Selector::PickedNo() {
	return Selector::GetChoice() == InputKeys::MENU_CHOICE_NO;
}

char Selector::GetChoice() {
	return choice;
}

void Selector::ResetChoice() {
	choice = -1;
}

void Selector::SetChoice(char ch) {
	choice = ch;
}

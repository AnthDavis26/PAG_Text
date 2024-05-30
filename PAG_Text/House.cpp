#include "House.h"
#include <iostream>
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Prompt.h"
#include "Utils.h"
#include "InputKeys.h"
#include "Rules.h"

void House::Start() {
	if (Rules::SAVE_AT_HOUSE) {
		SaveManager::SetAtHouse();
	}

	std::cout << "In house." << std::endl;
	std::cout << "\n'I am faced with a difficult decision: what do I do next?'" << std::endl;
	std::cout << "\n" << InputKeys::HOUSE_CHOICE_GOTO_KITCHEN << ". Go to the kitchen" << std::endl;
	std::cout << InputKeys::HOUSE_CHOICE_GOTO_BEDROOM << ". Go to the bedroom" << std::endl;
	std::cout << InputKeys::HOUSE_CHOICE_GOTO_BATHROOM << ". Go to the bathroom" << std::endl;
	std::cout << "Press P to pause." << std::endl;

	Prompt::PromptChoiceUntil([]() {
		return Prompt::GetChoice() == InputKeys::HOUSE_CHOICE_GOTO_KITCHEN
			|| Prompt::GetChoice() == InputKeys::HOUSE_CHOICE_GOTO_BEDROOM
			|| Prompt::GetChoice() == InputKeys::HOUSE_CHOICE_GOTO_BATHROOM
			|| Prompt::GetChoice() == 'p';
	});

	Utils::ClearScreen();

	switch (Prompt::GetChoice()) {
		case (InputKeys::HOUSE_CHOICE_GOTO_KITCHEN):
			Navigator::GoToHouseKitchen();
			return;
		case (InputKeys::HOUSE_CHOICE_GOTO_BEDROOM):
			Navigator::GoToHouseBedroom();
			return;
		case (InputKeys::HOUSE_CHOICE_GOTO_BATHROOM):
			Navigator::GoToHouseBathroom();
			return;
		case ('p'):
			Navigator::GoToPauseMenu();
			return;
		default:
			std::cout << "INVALID CHOICE (" << Prompt::GetChoice() << ")" << std::endl;
	}
}

void House::EnterKitchen() {
	std::cout << "I wanted to go to the bedroom, but I'm in the kitchen now." << std::endl;

	if (SaveManager::AteTrash()) {
		std::cout << "The trash is gone, but I still smell it somehow." << std::endl;
	} else {
		std::cout << "Hm, the trash is full." << std::endl;
	}

	std::cout << "\nWhat should I do?" << std::endl;
	std::cout << "1. Go to the bedroom" << std::endl;
	std::cout << "2. Go to the bathroom" << std::endl;
	std::cout << "3. ENTER PROMPT" << std::endl;
	std::cout << "Press P to pause." << std::endl;

	Prompt::PromptChoiceUntil([]() {
		return Prompt::GetChoice() == '1' || Prompt::GetChoice() == '2'
			|| Prompt::GetChoice() == '3'
			|| Prompt::GetChoice() == 'p';
	});

	Utils::ClearScreen();

	switch (Prompt::GetChoice()) {
		case ('1'):
			Navigator::GoToHouseBedroom();
			return;
		case ('2'):
			Navigator::GoToHouseBathroom();
			return;
		case ('3'):
			Prompt::CustomPrompt();
			Navigator::GoToHouseKitchen();
			return;
		case ('p'):
			Navigator::GoToPauseMenu();
			return;
		default:
			std::cout << "Invalid choice made." << std::endl;
	}
}

void House::EnterBedroom() {
	std::cout << "Bedroom's fine, though I could swear I intended to go to kitchen." << std::endl;
	std::cout << "\nLet me figure out how to proceed..." << std::endl;
	std::cout << "1. Go to the bathroom" << std::endl;
	std::cout << "2. Go to the kitchen" << std::endl;
	std::cout << "Press P to pause." << std::endl;

	Prompt::PromptChoiceUntil([]() {
		return Prompt::GetChoice() == '1' || Prompt::GetChoice() == '2'
			|| Prompt::GetChoice() == 'p';
	});

	Utils::ClearScreen();

	switch (Prompt::GetChoice()) {
		case ('1'):
			Navigator::GoToHouseBathroom();
			return;
		case ('2'):
			Navigator::GoToHouseKitchen();
			return;
		case ('p'):
			Navigator::GoToPauseMenu();
			return;
		default:
			std::cout << "Invalid choice made." << std::endl;
	}
}

void House::EnterBathroom() {
	std::cout << "What am I doing here? I want to go to the bedroom." << std::endl;
	std::cout << "\nI'm so confused. Now what?" << std::endl;
	std::cout << "1. Go to the kitchen" << std::endl;
	std::cout << "2. Go to the bedroom" << std::endl;
	std::cout << "Press P to pause." << std::endl;

	Prompt::PromptChoiceUntil([]() {
		return Prompt::GetChoice() == '1' || Prompt::GetChoice() == '2'
			|| Prompt::GetChoice() == 'p';
	});

	Utils::ClearScreen();

	switch (Prompt::GetChoice()) {
		case ('1'):
			Navigator::GoToHouseKitchen();
			return;
		case ('2'):
			Navigator::GoToHouseBedroom();
			return;
		case ('p'):
			Navigator::GoToPauseMenu();
			return;
		default:
			std::cout << "Invalid choice made." << std::endl;
	}
}
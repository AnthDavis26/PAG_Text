#include "House.h"
#include <iostream>
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Prompter.h"
#include "Utils.h"
#include "InputKeys.h"
#include "Rules.h"
#include "InputChecker.h"
#include "GameCharacters.h"

void House::Start() {
	House::EnterBedroom();
}

void House::EnterKitchen() {
	Prompter::SceneTitle("George's Kitchen");

	if (Rules::CAN_SAVE_AT_HOUSE_KITCHEN) {
		SaveManager::SetCurrentLocation(LocationKeys::HOUSE_KITCHEN);
	}

	std::string GeorgeDialogue = 
		"I wanted to go to the bedroom, but I'm in the kitchen now.\n";

	Navigator::SetCurrentLocationKey(LocationKeys::HOUSE_KITCHEN);

	if (SaveManager::AteHouseKitchenTrash()) {
		GeorgeDialogue += "The trash is gone, but I still smell it somehow.\n";
	} 
	else {
		GeorgeDialogue += "Hm, the trash is full. ";
	}

	GeorgeDialogue += "What should I do?";
	GameCharacters::GEORGE.Speak(GeorgeDialogue);

	Prompter::Print(
		"1. Go to the bedroom\n"
		"2. Go to the bathroom\n"
		"3. Go to the living room"
	);

	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		std::make_pair('1', Navigator::GoToHouseBedroom),
		std::make_pair('2', Navigator::GoToHouseBathroom),
		std::make_pair('3', Navigator::GoToHouseLivingRoom)
	);
}

void House::EnterBedroom() {
	Prompter::SceneTitle("George's Bedroom");

	if (Rules::CAN_SAVE_AT_HOUSE_BEDROOM) {
		SaveManager::SetCurrentLocation(LocationKeys::HOUSE_BEDROOM);
	}

	GameCharacters::GEORGE.Speak(
		"I'm fine here in my bedroom, but I'd rather be in the kitchen.\n"
		"Let me figure out how to proceed..."
	);

	Prompter::Print(
		"1. Go to the kitchen\n"
		"2. Go to the bathroom\n"
		"3. Go to the living room"
	);

	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		std::make_pair('1', Navigator::GoToHouseKitchen),
		std::make_pair('2', Navigator::GoToHouseBathroom),
		std::make_pair('3', Navigator::GoToHouseLivingRoom)
	);
}

void House::EnterLivingRoom() {
	Prompter::SceneTitle("George's Living Room");

	if (Rules::CAN_SAVE_AT_HOUSE_LIVING_ROOM) {
		SaveManager::SetCurrentLocation(LocationKeys::HOUSE_LIVING_ROOM);
	}

	GameCharacters::GEORGE.Speak(
		"It's not much of a living room, more of an existing room."
	);

	Prompter::Print(
		"1. Go to the kitchen\n"
		"2. Go to the bathroom\n"
		"3. Go to the bedroom\n"
		"4. Go outside"
	);

	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		std::make_pair('1', Navigator::GoToHouseKitchen),
		std::make_pair('2', Navigator::GoToHouseBathroom),
		std::make_pair('3', Navigator::GoToHouseBedroom),
		std::make_pair('4', Navigator::GoToHomeStreet)
	);

}

void House::EnterBathroom() {
	Prompter::SceneTitle("George's Bathroom");

	if (Rules::CAN_SAVE_AT_HOUSE_BATHROOM) {
		SaveManager::SetCurrentLocation(LocationKeys::HOUSE_BATHROOM);
	}

	GameCharacters::GEORGE.Speak(
		"What am I doing here? I want to go to the bedroom.\n"
		"I'm so confused. Now what?"
	);

	Prompter::Print(
		"1. Go to the bedroom\n"
		"2. Go to the kitchen\n"
		"3. Go to the living room"
	);

	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		std::make_pair('1', Navigator::GoToHouseBedroom),
		std::make_pair('2', Navigator::GoToHouseKitchen),
		std::make_pair('3', Navigator::GoToHouseLivingRoom)
	);
}
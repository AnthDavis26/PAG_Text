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

#define GEORGE GameCharacters::GEORGE

void House::Start() {
	House::EnterBedroom();
}

void House::EnterKitchen() {
	Prompter::SceneTitle(GEORGE.GetName() + "'s Kitchen");

	if (Rules::CAN_SAVE_AT_HOUSE_KITCHEN) {
		SaveManager::SetCurrentLocation(LocationKeys::HOUSE_KITCHEN);
	}

	std::string GeorgeDialogue = 
		"I wanted to go to the bedroom, but I'm in the kitchen now.\n";

	Navigator::SetCurrentLocationKey(LocationKeys::HOUSE_KITCHEN);

	if (SaveManager::AteHouseKitchenTrash()) {
		GeorgeDialogue += "The trash is gone, but I still smell it somehow.\n";
	} else {
		GeorgeDialogue += "Hm, the trash is full. ";
	}

	GeorgeDialogue += "What should I do?";
	GEORGE.Speak(GeorgeDialogue);

	Prompter::Print(
		"1. Go to the bedroom\n"
		"2. Go to the bathroom\n"
		"3. Go to the living room"
	);

	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		CMD('1', Navigator::GoToHouseBedroom),
		CMD('2', Navigator::GoToHouseBathroom),
		CMD('3', Navigator::GoToHouseLivingRoom)
	);
}

void House::EnterBedroom() {
	Prompter::SceneTitle(GEORGE.GetName() + "'s Bedroom");

	if (Rules::CAN_SAVE_AT_HOUSE_BEDROOM) {
		SaveManager::SetCurrentLocation(LocationKeys::HOUSE_BEDROOM);
	}

	GEORGE.Speak(
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
		CMD('1', Navigator::GoToHouseKitchen),
		CMD('2', Navigator::GoToHouseBathroom),
		CMD('3', Navigator::GoToHouseLivingRoom)
	);
}

void House::EnterLivingRoom() {
	Prompter::SceneTitle(GEORGE.GetName() + "'s Living Room");

	if (Rules::CAN_SAVE_AT_HOUSE_LIVING_ROOM) {
		SaveManager::SetCurrentLocation(LocationKeys::HOUSE_LIVING_ROOM);
	}

	GEORGE.Speak(
		"It's not much of a living room."
	);

	Prompter::Print(
		"1. Go to the kitchen\n"
		"2. Go to the bathroom\n"
		"3. Go to the bedroom\n"
		"4. Go outside"
	);

	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		CMD('1', Navigator::GoToHouseKitchen),
		CMD('2', Navigator::GoToHouseBathroom),
		CMD('3', Navigator::GoToHouseBedroom),
		CMD('4', Navigator::GoToHomeStreet)
	);

}

void House::EnterBathroom() {
	Prompter::SceneTitle(GEORGE.GetName() + "'s Bathroom");

	if (Rules::CAN_SAVE_AT_HOUSE_BATHROOM) {
		SaveManager::SetCurrentLocation(LocationKeys::HOUSE_BATHROOM);
	}

	GEORGE.Speak(
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
		CMD('1', Navigator::GoToHouseBedroom),
		CMD('2', Navigator::GoToHouseKitchen),
		CMD('3', Navigator::GoToHouseLivingRoom)
	);
}
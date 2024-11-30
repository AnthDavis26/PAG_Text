#include "HomeStreet.h"
#include "Prompter.h"
#include "LocationKeys.h"
#include "SaveManager.h"
#include "Rules.h"
#include "GameCharacters.h"

void HomeStreet::Start() {
	Prompter::SceneTitle("Street Avenue");

	if (Rules::CAN_SAVE_AT_HOME_STREET) {
		SaveManager::SetCurrentLocation(LocationKeys::HOME_STREET);
	}

	Prompter::Print(
		"You are outside your house. It takes a moment for your eyes\n"
		"to adjust to the sunlight after what feels like days.\n"
	);

	GameCharacters::GEORGE.Speak("I'm going to grow so many freckles.");

	Prompter::Print(
		"1. Go inside your house\n"
		"2. Walk to the diner"
	);

	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		CMD('1', Navigator::GoToHouseLivingRoom),
		CMD('2', Navigator::GoToDiner)
	);
}

#include "Diner.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Rules.h"
#include "Prompter.h"
#include "GameCharacters.h"

void Diner::Start() {
	Prompter::SceneTitle("Diner");

	if (Rules::CAN_SAVE_AT_DINER) {
		SaveManager::SetCurrentLocation(LocationKeys::DINER);
	}

	Prompter::Print("You're inside the local diner. It doesn't even have a proper name.\n");
	GameCharacters::GEORGE.Speak("Too bad they only serve condiments here.");
	Prompter::Print("1. Leave the diner");
	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		std::make_pair('1', Navigator::GoToHomeStreet)
	);
}

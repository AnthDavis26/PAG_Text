#include "PauseMenu.h"
#include "Navigator.h"
#include "Rules.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Prompter.h"
#include "Utils.h"
#include "InputChecker.h"

void PauseMenu::Start() {
	if (Rules::CAN_SAVE_AT_PAUSE_MENU) {
		SaveManager::SetAtPauseMenu();
	}

	Prompter::Print(
		"PAUSE MENU\n"
		"1. Resume\n"
		"2. Save As\n"
		"3. Exit Game"
	);

	Prompter::PromptUntilValidCommand(
		std::make_pair('1', PauseMenu::ResumeGame),
		std::make_pair('2', PauseMenu::SaveFileAs),
		std::make_pair('3', PauseMenu::ExitGame)
	);
}

void PauseMenu::ResumeGame() {
	Navigator::GoToCurrentLocation();
}

void PauseMenu::SaveFileAs() {
	Prompter::Print("Create new save file?");
	Prompter::PromptUntilYesOrNo();

	if (InputChecker::PickedNo()) {
		Navigator::GoToPauseMenu();
		return;
	}

	Prompter::Print("Save file as: (press ENTER to finish)");
	std::string name = Prompter::InputText();
	Utils::Trim(name);
	Prompter::ClearScreen();

	if (name.length() > Rules::MAX_FILE_NAME_LENGTH) {
		Prompter::Print(
			"File name " + name + " is too long (max name length is " 
			+ std::to_string(Rules::MAX_FILE_NAME_LENGTH)
			+ " characters). Please enter a shorter name."
		);

		PauseMenu::SaveFileAs();
		return;
	}
	else if (name.empty()) {
		Prompter::Print("File name cannot be blank.");
		Prompter::Print("");
		PauseMenu::SaveFileAs();
		return;
	}

	SaveFile sf(SaveManager::GetCurrentSaveFile().GetDirectory(),
		name, SaveManager::GetCurrentSaveFile().GetExtension());
	
	if (SaveManager::Contains(sf)) {
		Prompter::Print("File '" + sf.GetFileName() + "' already exists. Overwrite?");
		Prompter::PromptUntilYesOrNo();
		Prompter::ClearScreen();

		if (InputChecker::PickedYes()) {
			SaveManager::DeleteSaveAtIndex(SaveManager::IndexOf(sf));
		} 
		else {
			PauseMenu::SaveFileAs();
			return;
		}
	}

	Prompter::ClearScreen();
	SaveManager::CreateNewFile(sf);
	Navigator::GoToPauseMenu();
}

void PauseMenu::ExitGame() {
	Navigator::GoToMainMenu();
}

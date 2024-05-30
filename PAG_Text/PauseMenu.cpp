#include "PauseMenu.h"
#include "Navigator.h"
#include "Rules.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Prompt.h"
#include "Utils.h"

void PauseMenu::Start() {
	if (Rules::SAVE_AT_PAUSE_MENU) {
		SaveManager::SetAtPauseMenu();
	}

	std::cout << "PAUSE MENU" << std::endl;
	std::cout << "1. Resume" << std::endl;
	std::cout << "2. Save As" << std::endl;
	std::cout << "3. Exit Game" << std::endl;

	Prompt::PromptChoiceUntil([]() {
		return Prompt::GetChoice() == '1' || Prompt::GetChoice() == '2'
			|| Prompt::GetChoice() == '3';
	});

	Utils::ClearScreen();

	switch (Prompt::GetChoice()) {
		case ('1'):
			PauseMenu::ResumeGame();
			return;
		case ('2'):
			PauseMenu::SaveFileAs();
			return;
		case ('3'):
			PauseMenu::ExitGame();
			return;
		default:
			std::cout << "INVALID CHOICE (" << Prompt::GetChoice() << ")" << std::endl;
	}
}

void PauseMenu::ResumeGame() {
	Navigator::GoToSavedLocation();
}

void PauseMenu::SaveFileAs() {
	// Enter file name and press enter
	std::cout << "Create new save file?" << std::endl;
	Prompt::PromptYesOrNo();

	if (Prompt::PickedNo()) {
		Utils::ClearScreen();
		Navigator::GoToPauseMenu();
		return;
	}

	Utils::ClearScreen();
	std::cout << "Save file as: (press ENTER to finish)" << std::endl;
	std::string name = "";
	std::cin >> name;

	if (name.length() > Rules::MAX_FILE_NAME_LENGTH) {
		std::cout << "File name " << name << " is too long (max name length is "
			<< Rules::MAX_FILE_NAME_LENGTH << " characters). Please enter a shorter name."
			<< std::endl;
		PauseMenu::SaveFileAs();
	}

	Utils::ClearScreen();

	SaveFile sf(SaveManager::GetCurrentSaveFile().GetDirectory(),
		name, SaveManager::GetCurrentSaveFile().GetExtension());
	
	if (SaveManager::Contains(sf)) {
		std::cout << "File '" << sf.GetFileName() << "' already exists. Overwrite?" << std::endl;
		Prompt::PromptYesOrNo();
		Utils::ClearScreen();

		if (Prompt::PickedYes()) {
			SaveManager::DeleteSaveAtIndex(SaveManager::IndexOf(sf));
		} else {
			PauseMenu::SaveFileAs();
			return;
		}
	}
	SaveManager::CreateNewFile(sf);
	Navigator::GoToPauseMenu();
}

void PauseMenu::ExitGame() {
	Navigator::GoToMainMenu();
}

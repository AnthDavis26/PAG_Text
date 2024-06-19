#include "MainMenu.h"
#include "Utils.h"
#include <iostream>
#include <conio.h>
#include "Navigator.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Prompter.h"
#include "InputKeys.h"
#include "Rules.h"
#include "Strings.h"
#include "InputChecker.h"

int MainMenu::currentPageNumber;
int MainMenu::maxPossibleIndex;
int MainMenu::minSaveIndexOnPage;
int MainMenu::maxSaveIndexOnPage;

void MainMenu::Start() {
	if (Rules::CAN_SAVE_AT_MAIN_MENU) {
		SaveManager::SetAtMainMenu();
	}

	MainMenu::ResetFileSelectPage();
	Prompter::ShowGameInfo();
	Prompter::Print(
		"\n1. Resume Game\n"
		"2. New Game\n"
		"3. Load Save File\n"
		"4. Delete Save File\n"
		"5. Exit"
	);

	Prompter::PromptUntilValidCommand(
		std::make_pair( '1', MainMenu::ResumeGame),
		std::make_pair( '2', MainMenu::NewGame),
		std::make_pair( '3', MainMenu::LoadGame),
		std::make_pair( '4', MainMenu::DeleteFilesScreen),
		std::make_pair( '5', MainMenu::ExitGame)
	);
}

void MainMenu::ResumeGame() {
	Navigator::GoToSavedLocation();
}

void MainMenu::NewGame() {
	if (SaveManager::StartedGame()) {
		Prompter::Print(Strings::WARNING_OVERWRITE_WITH_NEW_GAME);
		Prompter::PromptUntilYesOrNo();
		Prompter::ClearScreen();

		if (InputChecker::PickedNo()) {
			Navigator::GoToMainMenu();
			return;
		}
	}

	SaveManager::ResetCurrentSaveFile();
	SaveManager::SetStartedGame();
	SaveManager::SetCurrentLocation(LocationKeys::HOUSE_BEDROOM);
	Navigator::GoToHouseBedroom();
}

void MainMenu::LoadGame() {
	SaveManager::InitSaveFiles();
	Prompter::Print("Load Save File");
	MainMenu::PrintSaveFiles();
	Prompter::Print("\nReturn: " + std::string{ InputKeys::RETURN });
	MainMenu::PrintFilePageChoices();
	Prompter::Print("");
	Prompter::PromptChoiceUntil(MainMenu::IsValidFileSelectScreenChoice);
	Prompter::ClearScreen();

	if (MainMenu::IsValidFileSelection()) {
		int index = Utils::CharNumToInt(Prompter::GetChoice()) + MainMenu::GetMinIndexOnPage() - 1;
		MainMenu::PrintOverwriteWithLoadWarning();
		Prompter::Print("\n");
		Prompter::PromptUntilYesOrNo();
		Prompter::ClearScreen();

		if (InputChecker::PickedNo()) {
			Navigator::GoToMainMenu();
			return;
		}

		SaveManager::OverwriteCurrentSaveFile(SaveManager::GetSaveFiles().at(index));
		Navigator::GoToSavedLocation();
	} 
	else {
		switch (Prompter::GetChoice()) {
			case InputKeys::PREV_PAGE:
				MainMenu::TurnPageBack();
				MainMenu::LoadGame();
				return;
			case InputKeys::NEXT_PAGE:
				MainMenu::TurnPageForward();
				MainMenu::LoadGame();
				return;
			case InputKeys::RETURN:
				Navigator::GoToMainMenu();
				return;
			default:
				Prompter::ShowInvalidChoice();
		}
	}
}


void MainMenu::DeleteFilesScreen() {
	SaveManager::InitSaveFiles();
	MainMenu::SetMaxPossibleIndex((int)SaveManager::GetSaveFiles().size() - 1);
	Prompter::Print("Delete Save File\n");
	MainMenu::PrintSaveFiles();
	Prompter::Print("Return: " + std::string{ InputKeys::RETURN });
	MainMenu::PrintFilePageChoices();
	Prompter::Print("");
	Prompter::PromptChoiceUntil(MainMenu::IsValidFileSelectScreenChoice);
	Prompter::ClearScreen();

	if (MainMenu::IsValidFileSelection()) {
		int index = Utils::CharNumToInt(Prompter::GetChoice()) + MainMenu::GetMinIndexOnPage() - 1;
		
		Prompter::Print("");
		Prompter::PromptUntilYesOrNo();

		if (InputChecker::PickedYes()) {
			SaveManager::DeleteSaveAtIndex(index);
		}

		MainMenu::ResetFileSelectPage();
		MainMenu::DeleteFilesScreen();
	} 
	else {
		switch (Prompter::GetChoice()) {
			case InputKeys::PREV_PAGE:
				MainMenu::TurnPageBack();
				MainMenu::DeleteFilesScreen();
				return;
			case InputKeys::NEXT_PAGE:
				MainMenu::TurnPageForward();
				MainMenu::DeleteFilesScreen();
				return;
			case InputKeys::RETURN:
				Navigator::GoToMainMenu();
				return;
			default:
				Prompter::ShowInvalidChoice();
		}
	}
}

void MainMenu::ExitGame() {
	Navigator::ExitGame();
}

void MainMenu::ResetFileSelectPage() {
	MainMenu::SetMaxPossibleIndex((int) SaveManager::GetSaveFiles().size() - 1);
	MainMenu::SetCurrentPageNumber(MainMenu::MIN_PAGE_NUMBER);
	MainMenu::SetMinIndexOnPage(MainMenu::MIN_POSSIBLE_INDEX);
	MainMenu::SetMaxIndexOnPage(std::min(MainMenu::MAX_FILES_ON_SELECT_SCREEN - 1,
		MainMenu::GetMaxPossibleIndex()));
}

void MainMenu::TurnPageBack() {
	MainMenu::SetMinIndexOnPage(MainMenu::GetMinIndexOnPage() - MainMenu::MAX_FILES_ON_SELECT_SCREEN);

	if (MainMenu::GetMinIndexOnPage() < 0) {
		MainMenu::ResetFileSelectPage();
	} 
	else {
		MainMenu::SetMaxIndexOnPage(MainMenu::GetMinIndexOnPage() + MainMenu::MAX_FILES_ON_SELECT_SCREEN - 1);
		MainMenu::SetCurrentPageNumber(MainMenu::GetCurrentPageNumber() - 1);
	}
}

void MainMenu::TurnPageForward() {
	MainMenu::SetMinIndexOnPage(MainMenu::GetMinIndexOnPage() + MainMenu::MAX_FILES_ON_SELECT_SCREEN);
	MainMenu::SetMaxIndexOnPage(MainMenu::GetMinIndexOnPage() + MainMenu::MAX_FILES_ON_SELECT_SCREEN - 1);

	if (MainMenu::GetMinIndexOnPage() >= MainMenu::GetMaxPossibleIndex()) {
		MainMenu::minSaveIndexOnPage = MainMenu::maxPossibleIndex;
	}

	if (MainMenu::maxSaveIndexOnPage >= MainMenu::maxPossibleIndex) {
		MainMenu::maxSaveIndexOnPage = MainMenu::maxPossibleIndex;
	}

	MainMenu::SetCurrentPageNumber(MainMenu::GetCurrentPageNumber() + 1);
}

void MainMenu::PrintSaveFiles() {
	Prompter::Print("Page: " + std::to_string(MainMenu::GetCurrentPageNumber()));

	if (SaveManager::GetSaveFiles().empty()) {
		Prompter::Print("No save files found.");
	} 
	else {
		int end = MainMenu::GetMaxIndexOnPage() - MainMenu::GetMinIndexOnPage() + 1;

		Prompter::Print("Enter choice from 1 to " + std::to_string(end) + ".");

		int n = MainMenu::GetMaxIndexOnPage();

		for (int i = MainMenu::GetMinIndexOnPage(), j = 1; i <= n; i++, j++) {
			Prompter::Print(std::to_string(j) + ". "
				+ SaveManager::GetSaveFiles()[i].GetFileName());
		}
	}
}

void MainMenu::PrintFilePageChoices() {
	if (MainMenu::IsPrevPagePossible()) {
		Prompter::Print("Previous Page: " + std::string{ InputKeys::PREV_PAGE });
	}

	if (MainMenu::IsPrevPagePossible() && MainMenu::IsNextPagePossible()) {
		Prompter::Print("\t");
	}

	if (MainMenu::IsNextPagePossible()) {
		Prompter::Print("Next Page: " + std::string{ InputKeys::NEXT_PAGE });
	}
}

void MainMenu::PrintOverwriteWithLoadWarning() {
	int index = MainMenu::GetMinIndexOnPage() + Utils::CharNumToInt(Prompter::GetChoice()) - 1;

	Prompter::Print("Overwrite current session with '" + SaveManager::GetSaveFiles().at(index).GetFileName());
	Prompter::Print(Strings::WARNING_OVERWRITE_WITH_LOAD_GAME);
}

void MainMenu::PrintDeleteFileWarning() {
	int index = Utils::CharNumToInt(Prompter::GetChoice()) - 1;
	Prompter::Print("Are you sure you wish to delete file '"
		+ SaveManager::GetSaveFiles().at(index).GetFileName() + "?\n"
		+ "This action CANNOT be undone!");
}

void MainMenu::SetCurrentPageNumber(int page) {
	MainMenu::currentPageNumber = page;
}

void MainMenu::SetMinIndexOnPage(int index) {
	MainMenu::minSaveIndexOnPage = index;
}

void MainMenu::SetMaxIndexOnPage(int index) {
	MainMenu::maxSaveIndexOnPage = index;
}

void MainMenu::SetMaxPossibleIndex(int index) {
	MainMenu::maxPossibleIndex = index;
}

int MainMenu::GetPageNumber() {
	return MainMenu::currentPageNumber;
}

int MainMenu::GetMinIndexOnPage() {
	return MainMenu::minSaveIndexOnPage;
}

int MainMenu::GetMaxIndexOnPage() {
	return MainMenu::maxSaveIndexOnPage;
}

int MainMenu::GetMaxPossibleIndex() {
	return MainMenu::maxPossibleIndex;
}

bool MainMenu::IsNextPagePossible() {
	return MainMenu::GetMaxIndexOnPage() < MainMenu::GetMaxPossibleIndex();
}

bool MainMenu::IsPrevPagePossible() {
	return MainMenu::GetCurrentPageNumber() > MainMenu::MIN_PAGE_NUMBER;
}

int MainMenu::GetCurrentPageNumber() {
	return MainMenu::currentPageNumber;
}

bool MainMenu::IsValidFileSelectScreenChoice() {
	char choice = Prompter::GetChoice();

	return choice == InputKeys::PREV_PAGE && MainMenu::IsPrevPagePossible()
		|| choice == InputKeys::NEXT_PAGE && MainMenu::IsNextPagePossible()
		|| choice == InputKeys::RETURN || IsValidFileSelection();
}

bool MainMenu::IsValidFileSelection() {
	int choice = Utils::CharNumToInt(Prompter::GetChoice());

	return choice >= 1 && choice <= 9 
		&& MainMenu::GetMinIndexOnPage() + choice - 1 <= MainMenu::GetMaxIndexOnPage();
}
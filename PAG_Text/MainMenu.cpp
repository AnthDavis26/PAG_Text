#include "MainMenu.h"
#include "Utils.h"
#include <iostream>
#include <conio.h>
#include "Navigator.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Prompt.h"
#include "InputKeys.h"
#include "Rules.h"

int MainMenu::currentPageNumber;
int MainMenu::maxPossibleIndex;
int MainMenu::minSaveIndexOnPage;
int MainMenu::maxSaveIndexOnPage;

void MainMenu::Start() {
	if (!SaveManager::StartedGame()) {
		Utils::ClearScreen();
		MainMenu::NewGame();
		return;
	}

	if (Rules::SAVE_AT_MAIN_MENU) {
		SaveManager::SetAtMainMenu();
	}

	MainMenu::ResetFileSelectPage();
	MainMenu::PrintGameInfo();
	std::cout << "\n" << std::endl;
	MainMenu::ShowMainMenuChoices();
	Prompt::PromptChoiceUntil(MainMenu::IsValidMainMenuChoice);
	Utils::ClearScreen();
	MainMenu::GoToChosenSelection();
}

void MainMenu::ShowMainMenuChoices() {
	std::cout << InputKeys::MENU_CHOICE_RESUME_GAME << ". Resume Game" << std::endl;
	std::cout << InputKeys::MENU_CHOICE_NEW_GAME << ". New Game" << std::endl;
	std::cout << InputKeys::MENU_CHOICE_LOAD_GAME << ". Load Save File" << std::endl;
	std::cout << InputKeys::MENU_CHOICE_DELETE_FILE << ". Delete Save File" << std::endl;
	std::cout << InputKeys::MENU_CHOICE_EXIT_GAME << ". Exit" << std::endl;
}

void MainMenu::ResumeGame() {
	Navigator::GoToSavedLocation();
}

void MainMenu::NewGame() {
	if (SaveManager::StartedGame()) {
		MainMenu::PrintOverwriteWithNewGameWarning();
		std::cout << "\n" << std::endl;
		Prompt::PromptYesOrNo();

		if (Prompt::PickedNo()) {
			Utils::ClearScreen();
			Navigator::GoToMainMenu();
			return;
		}
	}

	Utils::ClearScreen();
	SaveManager::GetCurrentSaveFile().Reset();
	SaveManager::SetStartedGame();
	Navigator::GoToHouse();
}

void MainMenu::LoadGame() {
	SaveManager::InitSaveFiles();
	std::cout << "Load Save File" << std::endl;
	MainMenu::PrintSaveFiles();
	std::cout << "\nReturn: " << InputKeys::RETURN << std::endl;
	MainMenu::PrintFilePageChoices();
	std::cout << std::endl;
	Prompt::PromptChoiceUntil(IsValidFileSelectScreenChoice);

	if (IsValidFileSelection()) {
		Utils::ClearScreen();
		int index = Utils::CharNumToInt(Prompt::GetChoice()) + MainMenu::GetMinIndexOnPage() - 1;
		MainMenu::PrintOverwriteWithLoadWarning();
		std::cout << "\n" << std::endl;
		Prompt::PromptYesOrNo();

		if (Prompt::PickedNo()) {
			Utils::ClearScreen();
			Navigator::GoToMainMenu();
			return;
		}

		SaveManager::OverwriteCurrentSaveFileWith(SaveManager::GetSaveFiles().at(index));
		Utils::ClearScreen();
		Navigator::GoToSavedLocation();
	} else {
		switch (Prompt::GetChoice()) {
			case InputKeys::PREV_PAGE:
				MainMenu::TurnPageBack();
				Utils::ClearScreen();
				MainMenu::LoadGame();
				return;
			case InputKeys::NEXT_PAGE:
				MainMenu::TurnPageForward();
				Utils::ClearScreen();
				MainMenu::LoadGame();
				return;
			case InputKeys::RETURN:
				Utils::ClearScreen();
				Navigator::GoToMainMenu();
				return;
			default:
				std::cout << "A valid file / file select screen choice should have been made. " <<
					"Something's not right. Please report this error to " << GameInfo::DEV_EMAIL << "."
					<< std::endl;
		}
	}
}


void MainMenu::DeleteFilesScreen() {
	SaveManager::InitSaveFiles();
	MainMenu::SetMaxPossibleIndex((int)SaveManager::GetSaveFiles().size() - 1);
	std::cout << "Delete Save File" << std::endl;
	MainMenu::PrintSaveFiles();
	std::cout << "\nReturn: " << InputKeys::RETURN << std::endl;
	MainMenu::PrintFilePageChoices();
	std::cout << std::endl;
	Prompt::PromptChoiceUntil(IsValidFileSelectScreenChoice);

	if (IsValidFileSelection()) {
		Utils::ClearScreen();
		int index = Utils::CharNumToInt(Prompt::GetChoice()) + MainMenu::GetMinIndexOnPage() - 1;
		MainMenu::PrintDeleteFileWarning();
		std::cout << "\n" << std::endl;
		Prompt::PromptYesOrNo();

		if (Prompt::PickedYes()) {
			SaveManager::DeleteSaveAtIndex(index);
		}

		MainMenu::ResetFileSelectPage();
		Utils::ClearScreen();
		MainMenu::DeleteFilesScreen();
	} else {
		switch (Prompt::GetChoice()) {
			case InputKeys::PREV_PAGE:
				MainMenu::TurnPageBack();
				Utils::ClearScreen();
				MainMenu::DeleteFilesScreen();
				return;
			case InputKeys::NEXT_PAGE:
				MainMenu::TurnPageForward();
				Utils::ClearScreen();
				MainMenu::DeleteFilesScreen();
				return;
			case InputKeys::RETURN:
				Utils::ClearScreen();
				Navigator::GoToMainMenu();
				return;
			default:
				std::cout << "A valid file / file select screen choice should have been made. " <<
					"Something's not right. Please report this error to " << GameInfo::DEV_EMAIL << "."
					<< std::endl;
		}
	}
}

void MainMenu::ExitGame() {
	Navigator::ExitGame();
}

bool MainMenu::IsValidMainMenuChoice() {
	char choice = Prompt::GetChoice();

	return choice == InputKeys::MENU_CHOICE_RESUME_GAME ||
		choice == InputKeys::MENU_CHOICE_NEW_GAME ||
		choice == InputKeys::MENU_CHOICE_LOAD_GAME ||
		choice == InputKeys::MENU_CHOICE_DELETE_FILE ||
		choice == InputKeys::MENU_CHOICE_EXIT_GAME;
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
	} else {
		MainMenu::SetMaxIndexOnPage(MainMenu::GetMinIndexOnPage() + MainMenu::MAX_FILES_ON_SELECT_SCREEN - 1);
		MainMenu::SetCurrentPageNumber(MainMenu::GetCurrentPageNumber() - 1);
	}
}

void MainMenu::TurnPageForward() {
	MainMenu::SetMinIndexOnPage(MainMenu::GetMinIndexOnPage() + MainMenu::MAX_FILES_ON_SELECT_SCREEN);
	MainMenu::SetMaxIndexOnPage(MainMenu::GetMinIndexOnPage() + MainMenu::MAX_FILES_ON_SELECT_SCREEN - 1);

	if (MainMenu::GetMinIndexOnPage() >= MainMenu::GetMaxPossibleIndex()) {
		minSaveIndexOnPage = MainMenu::maxPossibleIndex;
	}

	if (maxSaveIndexOnPage >= MainMenu::maxPossibleIndex) {
		maxSaveIndexOnPage = MainMenu::maxPossibleIndex;
	}

	MainMenu::SetCurrentPageNumber(MainMenu::GetCurrentPageNumber() + 1);
}

void MainMenu::GoToChosenSelection() {
	switch (Prompt::GetChoice()) {
		case InputKeys::MENU_CHOICE_RESUME_GAME:
			MainMenu::ResumeGame();
			break;
		case InputKeys::MENU_CHOICE_NEW_GAME:
			MainMenu::NewGame();
			break;
		case InputKeys::MENU_CHOICE_LOAD_GAME:
			MainMenu::LoadGame();
			break;
		case InputKeys::MENU_CHOICE_DELETE_FILE:
			MainMenu::DeleteFilesScreen();
			break;
		case InputKeys::MENU_CHOICE_EXIT_GAME:
			MainMenu::ExitGame();
			break;
		default:
			ShowInvalidMenuSelectMessage();
	}
}

void MainMenu::SaveProgress() {
	SaveManager::SetCurrentLocation(LocationKeys::MAIN_MENU);
}

void MainMenu::PrintGameInfo() {
	std::cout << GameInfo::TITLE << std::endl;
	std::cout << GameInfo::COPYRIGHT << std::endl;
}

void MainMenu::PrintSaveFiles() {
	std::cout << "Page: " << MainMenu::GetCurrentPageNumber() << "\n" << std::endl;
	//std::cout << "MIN INDEX: " << MainMenu::minSaveIndexOnPage << std::endl;
	//std::cout << "MAX INDEX: " << MainMenu::maxSaveIndexOnPage << std::endl;
	//std::cout << "MAX POSSIBLE INDEX : " << MainMenu::maxPossibleIndex << std::endl;
	if (SaveManager::GetSaveFiles().empty()) {
		std::cout << "No save files found." << std::endl;
	} else {
		std::cout << "Enter a choice from 1 to "
			<< (MainMenu::GetMaxIndexOnPage() - MainMenu::GetMinIndexOnPage() + 1)		
			<< "." << std::endl;
		for (int i = MainMenu::GetMinIndexOnPage(), j = 1; i <= MainMenu::GetMaxIndexOnPage(); i++, j++) {
			std::cout << j << ". " << SaveManager::GetSaveFiles()[i].GetFileName();
			//std::cout << " (INDEX: " << i << ")";
			std::cout << std::endl;
		}
	}
}

void MainMenu::PrintFilePageChoices() {
	if (MainMenu::IsPrevPagePossible()) {
		std::cout << "Previous Page: " << InputKeys::PREV_PAGE;
	}

	if (MainMenu::IsPrevPagePossible() && MainMenu::IsNextPagePossible()) {
		std::cout << "\t";
	}

	if (MainMenu::IsNextPagePossible()) {
		std::cout << "Next Page: " << InputKeys::NEXT_PAGE;
	}
}

void MainMenu::PrintOverwriteWithNewGameWarning() {
	std::cout << "Restart progress?\n\nWARNING: You'll LOSE all progress you've made! "
		<< "\nIf you want to back up your save, resume game and then choose 'SAVE GAME'."
		<< "\n\nTHIS CANNOT BE UNDONE! Are you ABSOLUTELY sure you want to restart?";
}

void MainMenu::PrintOverwriteWithLoadWarning() {
	int index = MainMenu::GetMinIndexOnPage() + Utils::CharNumToInt(Prompt::GetChoice()) - 1;
	std::cout << "Overwrite current session with '" << SaveManager::GetSaveFiles().at(index).GetFileName()
		<< "'?\n\nWARNING: You will lose ALL progress you have made so far!"
		<< "\nIf you want to back up your save, resume game and then choose 'SAVE GAME'."
		<< "\n\nTHIS CANNOT BE UNDONE! Are you ABSOLUTELY sure you want to load this file?";
}

void MainMenu::PrintDeleteFileWarning() {
	int index = Utils::CharNumToInt(Prompt::GetChoice()) - 1;
	std::cout << "Are you sure you wish to delete file '" << SaveManager::GetSaveFiles().at(index).GetFileName()
		<< "'?\nThis action CANNOT be undone!";
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
	char choice = Prompt::GetChoice();

	return choice == InputKeys::PREV_PAGE && MainMenu::IsPrevPagePossible()
		|| choice == InputKeys::NEXT_PAGE && MainMenu::IsNextPagePossible()
		|| choice == InputKeys::RETURN || IsValidFileSelection();
}

bool MainMenu::IsValidFileSelection() {
	int choice = Utils::CharNumToInt(Prompt::GetChoice());
	return choice >= 1 && choice <= 9 
		&& MainMenu::GetMinIndexOnPage() + choice - 1 <= MainMenu::GetMaxIndexOnPage();
}

void MainMenu::ShowInvalidMenuSelectMessage() {
	std::cout << "INVALID MAIN MENU SELECTION. This should not happen. Please report"
		<< " this error to the dev at " << GameInfo::DEV_EMAIL << "." << std::endl;
}
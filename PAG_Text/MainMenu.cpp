#include "MainMenu.h"
#include "Utils.h"
#include <iostream>
#include <conio.h>
#include "Navigator.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Selector.h"

int MainMenu::page = 1;
int MainMenu::lowestSaveNumOnPage = 0;
int MainMenu::furthestSaveNumOnPage = 8;

void MainMenu::Start() {
	if (!SaveManager::StartedGame()) {
		Utils::ClearScreen();
		MainMenu::NewGame();
		return;
	}
	MainMenu::ResetPage();
	ShowGameInfo();
	std::cout << "\n" << std::endl;
	ShowMainMenuChoices();
	Selector::PromptAndGetChoice(MainMenu::IsValidMainMenuChoice);
	Utils::ClearScreen();
	MainMenu::GoToChosenSelection();
}


bool MainMenu::IsValidMainMenuChoice() {
	char choice = Selector::GetChoice();

	return choice == MENU_CHOICE_RESUME_GAME ||
		choice == MENU_CHOICE_NEW_GAME ||
		choice == MENU_CHOICE_LOAD_GAME ||
		choice == MENU_CHOICE_DELETE_FILE ||
		choice == MENU_CHOICE_EXIT_GAME;
}

void MainMenu::ResetPage() {
	lowestSaveNumOnPage = 0;
	furthestSaveNumOnPage = 8;
	page = 1;
}

void MainMenu::TurnPageBack() {
	if (page > 1) {
		lowestSaveNumOnPage -= 8;
		furthestSaveNumOnPage -= 8;
		page--;
	}
}

void MainMenu::TurnPageForward() {
	if (furthestSaveNumOnPage < SaveManager::GetSaveFiles().size()) {
		furthestSaveNumOnPage = std::min(furthestSaveNumOnPage + 8, (int) SaveManager::GetSaveFiles().size());
		lowestSaveNumOnPage += 8;
		page++;
	}
}

void MainMenu::GoToChosenSelection() {
	switch (Selector::GetChoice()) {
	case MENU_CHOICE_RESUME_GAME:
		MainMenu::ResumeGame();
		break;
	case MENU_CHOICE_NEW_GAME:
		MainMenu::NewGame();
		break;
	case MENU_CHOICE_LOAD_GAME:
		MainMenu::LoadGame();
		break;
	case MENU_CHOICE_DELETE_FILE:
		MainMenu::DeleteFilesScreen();
		break;
	case MENU_CHOICE_EXIT_GAME:
		MainMenu::ExitGame();
		break;
	default:
		ShowInvalidMenuSelectMessage();
	}
}

void MainMenu::SaveProgress() {
	SaveManager::SetCurrentLocation(LocationKeys::KEY_LOC_MAIN_MENU);
}

void MainMenu::ShowMainMenuChoices() {
	std::cout << MENU_CHOICE_RESUME_GAME << ". Resume Game" << std::endl;
	std::cout << MENU_CHOICE_NEW_GAME << ". New Game" << std::endl;
	std::cout << MENU_CHOICE_LOAD_GAME << ". Load Save File" << std::endl;
	std::cout << MENU_CHOICE_DELETE_FILE << ". Delete Save File" << std::endl;
	std::cout << MENU_CHOICE_EXIT_GAME << ". Exit" << std::endl;
}

void MainMenu::ShowGameInfo() {
	std::cout << GameInfo::TITLE << std::endl;
	std::cout << GameInfo::COPYRIGHT << std::endl;
}

void MainMenu::PrintSaveFiles() {
	if (SaveManager::GetSaveFiles().empty()) {
		std::cout << "No save files found." << std::endl;
	} else {
		for (int i = lowestSaveNumOnPage, j = 1; i < furthestSaveNumOnPage; i++, j++) {
			std::cout << j << ". " << SaveManager::GetSaveFiles()[i].GetFileName() << std::endl;
		}
	}
}

void MainMenu::LoadGame() {
	std::cout << "Load Save File" << std::endl;
	MainMenu::PrintSaveFiles();
	std::cout << "\nReturn: " << RETURN_KEY << "\nLeft Page: " << PREV_PAGE_KEY
		<< "\tNext Page: " << NEXT_PAGE_KEY << std::endl;

	char choice = Selector::PromptAndGetChoice(IsValidFileSelectScreenChoice);

	if (IsValidFileSelection()) {
		choice = Utils::CharNumToInt(choice);
		choice += lowestSaveNumOnPage;
		SaveManager::OverwriteCurrentSaveFile(SaveManager::GetSaveFiles().at(choice - 1));
		Utils::ClearScreen();
		Navigator::GoToSavedLocation();
	} else {
		switch (choice) {
		case PREV_PAGE_KEY:
			MainMenu::TurnPageBack();
			Utils::ClearScreen();
			MainMenu::LoadGame();
			break;
		case NEXT_PAGE_KEY:
			MainMenu::TurnPageForward();
			Utils::ClearScreen();
			MainMenu::LoadGame();
			break;
		case RETURN_KEY:
			Utils::ClearScreen();
			Navigator::GoToMainMenu();
			break;
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

int MainMenu::GetPageNumber() {
	return page;
}

bool MainMenu::IsValidFileSelectScreenChoice() {
	char choice = Selector::GetChoice();
	return (choice == PREV_PAGE_KEY || choice == NEXT_PAGE_KEY || choice == RETURN_KEY)
		|| IsValidFileSelection();
}

bool MainMenu::IsValidFileSelection() {
	char choice = Utils::CharNumToInt(Selector::GetChoice());
	return choice >= 1 && choice <= 9 && choice <= SaveManager::GetSaveFiles().size();
}

void MainMenu::DeleteFilesScreen() {
	std::cout << "Delete Save File" << std::endl;
	MainMenu::PrintSaveFiles();
}

void MainMenu::ResumeGame() {
	Navigator::GoToSavedLocation();
}

bool MainMenu::IsValidRestartProgressChoice() {
	return Selector::GetChoice() == '1' || Selector::GetChoice() == '2';
}

void MainMenu::NewGame() {
	if (SaveManager::StartedGame()) {
		std::cout << "Restart progress?\n1. Yes\t2. No" << std::endl;
		char choice = Selector::PromptAndGetChoice(MainMenu::IsValidRestartProgressChoice);

		if (choice == '2') {
			Utils::ClearScreen();
			Navigator::GoToMainMenu();
			return;
		}
	}
	Utils::ClearScreen();
	SaveManager::GetCurrentSaveFile().Reset();
	SaveManager::SetStartedGame(true);
	Navigator::GoToHouse();
	SaveManager::SetAtHouse(true);
}

void MainMenu::ShowInvalidMenuSelectMessage() {
	std::cout << "INVALID MAIN MENU SELECTION. This should not happen. Please report"
		<< " this error to the dev at " << GameInfo::DEV_EMAIL << "." << std::endl;
}
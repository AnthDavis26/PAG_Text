#include "Navigator.h"
#include <iostream>
#include <conio.h>
#include "Utils.h"
#include "GameInfo.h"
#include "MainMenu.h"
#include "House.h"
#include "LocationKeys.h"
#include "SaveManager.h"
#include "Diner.h"

void Navigator::GoTo(int locationKey) {
	switch (locationKey)
	{
		case LocationKeys::MAIN_MENU:
			GoToMainMenu();
			break;
		case LocationKeys::HOUSE:
			GoToHouse();
			break;
		case LocationKeys::DINER:
			GoToDiner();
			break;
		default:
			GoToTest();
	}
}

void Navigator::GoToSavedLocation() {
	Navigator::GoTo(SaveManager::GetCurrentLocationKey());
}

void Navigator::GoToMainMenu() {
	MainMenu::Start();
}

void Navigator::GoToHouse() {
	House::Start();
}

void Navigator::GoToDiner() {
	Diner::Start();
}

void Navigator::GoToTest() {
	std::cout << "In test location." << std::endl;
}

void Navigator::ExitGame() {
	exit(0);
}

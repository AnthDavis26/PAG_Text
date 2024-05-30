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
#include "PauseMenu.h"

int Navigator::currentLocationKey = -1;

bool Navigator::AtHouseKitchen() {
	return Navigator::GetCurrentLocationKey() == LocationKeys::HOUSE_KITCHEN;
}

int Navigator::GetCurrentLocationKey() {
	return currentLocationKey;
}

void Navigator::SetCurrentLocationKey(int locationKey) {
	currentLocationKey = locationKey;
}

void Navigator::GoTo(int locationKey) {
	Navigator::SetCurrentLocationKey(locationKey);

	switch (locationKey) {
		case LocationKeys::MAIN_MENU:
			Navigator::GoToMainMenu();
			return;
		case LocationKeys::HOUSE:
			Navigator::GoToHouse();
			return;
		case LocationKeys::DINER:
			Navigator::GoToDiner();
			return;
		default:
			Navigator::GoToTest();
	}
}

void Navigator::GoToSavedLocation() {
	Navigator::SetCurrentLocationKey(SaveManager::GetCurrentLocationKey());
	Navigator::GoTo(SaveManager::GetCurrentLocationKey());
}

void Navigator::GoToMainMenu() {
	Navigator::SetCurrentLocationKey(LocationKeys::MAIN_MENU);
	MainMenu::Start();
}

void Navigator::GoToPauseMenu() {
	Navigator::SetCurrentLocationKey(LocationKeys::PAUSE_MENU);
	PauseMenu::Start();
}

void Navigator::GoToHouse() {
	Navigator::SetCurrentLocationKey(LocationKeys::HOUSE);
	House::Start();
}

void Navigator::GoToHouseBedroom() {
	Navigator::SetCurrentLocationKey(LocationKeys::HOUSE_BEDROOM);
	House::EnterBedroom();
}

void Navigator::GoToHouseBathroom() {
	Navigator::SetCurrentLocationKey(LocationKeys::HOUSE_BATHROOM);
	House::EnterBathroom();
}

void Navigator::GoToHouseKitchen() {
	Navigator::SetCurrentLocationKey(LocationKeys::HOUSE_KITCHEN);
	House::EnterKitchen();
}

void Navigator::GoToDiner() {
	Navigator::SetCurrentLocationKey(LocationKeys::DINER);
	Diner::Start();
}

void Navigator::GoToTest() {
	Navigator::SetCurrentLocationKey(LocationKeys::TEST);
	std::cout << "In test location." << std::endl;
}

void Navigator::ExitGame() {
	exit(0);
}

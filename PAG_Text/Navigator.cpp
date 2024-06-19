#include "Navigator.h"
#include <iostream>
#include <conio.h>
#include "Utils.h"
#include "MainMenu.h"
#include "House.h"
#include "LocationKeys.h"
#include "SaveManager.h"
#include "Diner.h"
#include "PauseMenu.h"
#include "Rules.h"
#include "Prompter.h"
#include "HomeStreet.h"

int Navigator::currentLocationKey = -1;
bool Navigator::locationsInitialized = false;
std::unordered_map<int, std::function<void()>> Navigator::validLocations;

void Navigator::InitLocations() {
	if (!Navigator::locationsInitialized) {
		Navigator::validLocations.insert({ LocationKeys::MAIN_MENU, MainMenu::Start });
		Navigator::validLocations.insert({ LocationKeys::PAUSE_MENU, PauseMenu::Start });
		Navigator::validLocations.insert({ LocationKeys::HOUSE_BATHROOM, House::EnterBathroom });
		Navigator::validLocations.insert({ LocationKeys::HOUSE_BEDROOM, House::EnterBedroom });
		Navigator::validLocations.insert({ LocationKeys::HOUSE_KITCHEN, House::EnterKitchen });
		Navigator::validLocations.insert({ LocationKeys::HOUSE_LIVING_ROOM, House::EnterLivingRoom });
		Navigator::validLocations.insert({ LocationKeys::HOME_STREET, HomeStreet::Start });
		Navigator::validLocations.insert({ LocationKeys::DINER, Diner::Start });
		Navigator::locationsInitialized = true;
	}
}

void Navigator::GoToCurrentLocation() {
	Navigator::GoTo(Navigator::GetCurrentLocationKey());
}

int Navigator::GetCurrentLocationKey() {
	return Navigator::currentLocationKey;
}

bool Navigator::AtHouseKitchen() {
	return Navigator::GetCurrentLocationKey() == LocationKeys::HOUSE_KITCHEN;
}

void Navigator::SetCurrentLocationKey(int locationKey) {
	Navigator::currentLocationKey = locationKey;
}

void Navigator::GoTo(int locationKey) {
	bool isMainMenu = locationKey == LocationKeys::MAIN_MENU;
	bool isPauseMenu = locationKey == LocationKeys::PAUSE_MENU;

	if (!isMainMenu && !isPauseMenu || (isMainMenu && Rules::CAN_SET_MAIN_MENU_AS_CURRENT_LOCATION)
		|| (isPauseMenu && Rules::CAN_SET_PAUSE_MENU_AS_CURRENT_LOCATION)) {
		Navigator::SetCurrentLocationKey(locationKey);
	}

	Navigator::validLocations.find(locationKey)->second();
}

void Navigator::GoToMainMenu() {
	Navigator::GoTo(LocationKeys::MAIN_MENU);
}

void Navigator::GoToHouseLivingRoom() {
	Navigator::GoTo(LocationKeys::HOUSE_LIVING_ROOM);
}

void Navigator::GoToHouseBedroom() {
	Navigator::GoTo(LocationKeys::HOUSE_BEDROOM);
}

void Navigator::GoToHouseBathroom() {
	Navigator::GoTo(LocationKeys::HOUSE_BATHROOM);
}

void Navigator::GoToHomeStreet() {
	Navigator::GoTo(LocationKeys::HOME_STREET);
}

void Navigator::GoToDiner() {
	Navigator::GoTo(LocationKeys::DINER);
}

void Navigator::GoToHouseKitchen() {
	Navigator::GoTo(LocationKeys::HOUSE_KITCHEN);
}

void Navigator::GoToPauseMenu() {
	Navigator::GoTo(LocationKeys::PAUSE_MENU);
}

void Navigator::GoToSavedLocation() {
	Navigator::GoTo(SaveManager::GetCurrentLocationKey());
}

void Navigator::ExitGame() {
	std::exit(0);
}

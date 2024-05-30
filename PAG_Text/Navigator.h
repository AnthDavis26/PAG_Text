#pragma once
#include "Location.h"

class Navigator {
	public:
		static bool AtHouseKitchen();
		static int GetCurrentLocationKey();
		static void SetCurrentLocationKey(int);
		static void GoTo(int locationKey);
		static void GoToSavedLocation();
		static void GoToMainMenu();
		static void GoToPauseMenu();
		static void GoToHouse();
		static void GoToHouseBedroom();
		static void GoToHouseBathroom();
		static void GoToHouseKitchen();
		static void GoToDiner();
		static void GoToTest();
		static void ExitGame();
	private:
		static int currentLocationKey;
};


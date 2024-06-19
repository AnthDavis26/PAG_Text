#pragma once
#include "Location.h"

class Navigator {
	public:
		static int GetCurrentLocationKey();
		static bool AtHouseKitchen();
		static void InitLocations();
		static void GoToCurrentLocation();
		static void SetCurrentLocationKey(int);
		static void GoTo(int locationKey);
		static void GoToMainMenu();
		static void GoToPauseMenu();
		static void GoToHouseLivingRoom();
		static void GoToHouseBedroom();
		static void GoToHouseKitchen();
		static void GoToHouseBathroom();
		static void GoToHomeStreet();
		static void GoToDiner();
		static void GoToSavedLocation();
		static void ExitGame();
	private:
		static bool locationsInitialized;
		static int currentLocationKey;
		static std::unordered_map<int, std::function<void()>> validLocations;
};


#pragma once
#include "Location.h"
#include <map>

class Navigator {
	public:
		static void GoTo(int locationKey);
		static void GoToSavedLocation();
		static void GoToMainMenu();
		static void GoToHouse();
		static void GoToDiner();
		static void GoToTest();
		static void ExitGame();
	private:
};


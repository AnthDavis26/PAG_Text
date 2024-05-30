#pragma once
#include "Location.h"

class PauseMenu : public Location {
	public:
		static void Start();
		static void ResumeGame();
		static void SaveFileAs();
		static void ExitGame();
};


#pragma once
#include "Location.h"

class PauseMenu : public Location
{
public:
	static void ResumeGame();
	static void SaveFileAs();
	static void ExitGame();
private:
};


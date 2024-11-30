#include "Navigator.h"
#include "SaveManager.h"
#include "MainMenu.h"

// Flow
int main() {
	Navigator::InitLocations();
	SaveManager::InitSaveFiles();
	SaveManager::DEBUG_CheckAllOverlaps();
	
	if (SaveManager::StartedGame()) {
		Navigator::GoToMainMenu();
	} else {
		MainMenu::NewGame();
	}

    return 0;
}
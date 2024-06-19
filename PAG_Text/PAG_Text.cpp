#include "Navigator.h"
#include "SaveManager.h"
#include "MainMenu.h"

// Flow
int main() {
	Navigator::InitLocations();
	SaveManager::InitSaveFiles();
	
	if (SaveManager::StartedGame()) {
		Navigator::GoToMainMenu();
	}
	else {
		MainMenu::NewGame();
	}

    return 0;
}
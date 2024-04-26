#include "Navigator.h"
#include "SaveManager.h"

// Flow
int main() {
	SaveManager::InitSaveFiles();
	Navigator::GoToMainMenu();
	return 0;
}
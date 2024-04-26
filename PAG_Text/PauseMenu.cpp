#include "PauseMenu.h"
#include "Navigator.h"

void PauseMenu::ResumeGame()
{
	Navigator::GoToSavedLocation();
}

void PauseMenu::ExitGame()
{
	Navigator::GoToMainMenu();
}

#pragma once
#include "GameInfo.h"
#include "Location.h"

class MainMenu : public Location
{
public:
    static void Start();
    static void ShowGameInfo();
    static void PrintSaveFiles();
    static bool IsValidFileSelectScreenChoice();
    static bool IsValidFileSelection();
    static void DeleteFilesScreen();
    static void ResumeGame();
    static bool IsValidRestartProgressChoice();
    static void NewGame();
    static void LoadGame();
    static void DeleteSave();
    static void ExitGame();
    static int GetPageNumber();
private:
    static void ResetPage();
    static void TurnPageBack();
    static void TurnPageForward();
    static void GoToChosenSelection();
    static void SaveProgress();
    static void ShowMainMenuChoices();
    static void ShowInvalidMenuSelectMessage();
    static bool IsValidMainMenuChoice();
    static constexpr char MENU_CHOICE_RESUME_GAME = '1';
    static constexpr char MENU_CHOICE_NEW_GAME = '2';
    static constexpr char MENU_CHOICE_LOAD_GAME = '3';
    static constexpr char MENU_CHOICE_DELETE_FILE = '4';
    static constexpr char MENU_CHOICE_EXIT_GAME = '5';
    static constexpr char PREV_PAGE_KEY = 'q';
    static constexpr char NEXT_PAGE_KEY = 'e';
    static constexpr char RETURN_KEY = '`';
    static int page;
    static int furthestSaveNumOnPage;
    static int lowestSaveNumOnPage;
    static constexpr int MAX_FILES_ON_SELECT_SCREEN = 9;
};


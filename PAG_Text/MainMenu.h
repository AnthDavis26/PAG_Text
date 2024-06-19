#pragma once
#include "Location.h"

class MainMenu : public Location {
    public:
        static void Start();
        static void PrintSaveFiles();
        static void PrintFilePageChoices();
        static bool IsValidFileSelectScreenChoice();
        static bool IsValidFileSelection();
        static void DeleteFilesScreen();
        static void ResumeGame();
        static void NewGame();
        static void LoadGame();
        static void ExitGame();
        static int GetPageNumber();
    private:
        static void ResetFileSelectPage();
        static void TurnPageBack();
        static void TurnPageForward();
        static bool IsNextPagePossible();
        static bool IsPrevPagePossible();
        static int GetCurrentPageNumber();
        static int GetMinIndexOnPage();
        static int GetMaxIndexOnPage();
        static int GetMaxPossibleIndex();
        static void SetCurrentPageNumber(int);
        static void SetMinIndexOnPage(int);
        static void SetMaxIndexOnPage(int);
        static void SetMaxPossibleIndex(int);
        static void PrintOverwriteWithLoadWarning();
        static void PrintDeleteFileWarning();
        static constexpr int MIN_PAGE_NUMBER = 1;
        static constexpr int MIN_POSSIBLE_INDEX = 0;
        static int currentPageNumber; 
        static int maxPossibleIndex;
        static int minSaveIndexOnPage;
        static int maxSaveIndexOnPage;
        static constexpr int MAX_FILES_ON_SELECT_SCREEN = 9;
};


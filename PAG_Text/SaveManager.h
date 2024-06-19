#pragma once
#include "Location.h"
#include "Navigator.h"
#include "SaveFile.h"
#include <filesystem>
#include <vector>

class SaveManager {
public:
    static const SaveFile& GetCurrentSaveFile();
    static const std::vector<SaveFile>& GetSaveFiles();
    static bool AteHouseKitchenTrash();
    static bool StartedGame();
    static bool Contains(const SaveFile&);
    static int IndexOf(const SaveFile& sf);
    static int GetCurrentLocationKey();

    static void CreateNewFile(const SaveFile& sf);
    static void SetCurrentLocation(int locationKey);
    static void SetAtMainMenu();
    static void SetAtPauseMenu();
    static void SetAteHouseKitchenTrash();
    static void SetAtHouse();
    static void SetAtDiner();
    static void SetStartedGame();
    static void DeleteSaveAtIndex(int index);
    static void OverwriteCurrentSaveFile(const SaveFile& sf);

    static void ResetCurrentSaveFile();
    static void InitSaveFiles();
    static void SortFiles();
    static void DEBUG_CheckAllOverlaps();
private:
    static void ClearSaveFiles();
    static void OverwriteSaveFile(const SaveFile& source, const SaveFile& destination);

    static std::vector<SaveFile> saveFiles;
    static SaveFile currentSaveFile;
    static int ADDRESS_CURRENT_LOCATION;
    static int ADDRESS_STARTED_GAME;
    static int FLAG_POS_STARTED_GAME;
    static int ADDRESS_ATE_HOUSE_TRASH;
    static int FLAG_POS_ATE_HOUSE_TRASH;
};

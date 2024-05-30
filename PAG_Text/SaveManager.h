#pragma once
#include <vector>
#include <filesystem>
#include "SaveFile.h"
#include "Location.h"
#include "Navigator.h"

class SaveManager {
	public:
		static SaveFile GetCurrentSaveFile();
		static int GetCurrentLocationKey();
		static std::vector<SaveFile>& GetSaveFiles();
		static bool AteTrash();
		static bool StartedGame();
		static bool Contains(SaveFile);
		static int IndexOf(SaveFile);

		static void CreateNewFile(SaveFile);
		static void OverwriteSaveFile(SaveFile source, SaveFile destination);
		static void OverwriteCurrentSaveFileWith(SaveFile);
		static void SetCurrentLocation(int locationKey);
		static void SetAtMainMenu();
		static void SetAtPauseMenu();
		static void SetAteHouseTrash();
		static void SetAtHouse();
		static void SetAtDiner();
		static void SetStartedGame();
		static void DeleteSaveAtIndex(int);

		static void InitSaveFiles();
		static void SortFiles();
		static void DEBUG_CheckAllOverlaps();
	private:
		static void ClearSaveFiles();

		static std::vector<SaveFile> saveFiles;
		static const int ADDRESS_CURRENT_LOCATION = 0x00000000;

		static const int ADDRESS_STARTED_GAME = 0x0000000F;
		static const int FLAG_POS_STARTED_GAME = 0;

		static const int ADDRESS_ATE_HOUSE_TRASH = 0x000000FF;
		static const int FLAG_POS_ATE_HOUSE_TRASH = 0;

		static const std::string SAVE_DEFAULT_DIRECTORY;
		static const std::string SAVE_DEFAULT_EXTENSION;
		static const std::string SAVE_CURRENT_NAME;
};


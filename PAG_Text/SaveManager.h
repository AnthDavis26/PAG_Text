#pragma once
#include <vector>
#include "SaveFile.h"
#include <filesystem>
#include "Location.h"
#include "Navigator.h"

class SaveManager {
	public:
		static void DEBUG_CheckAllOverlaps();
		static void OverwriteCurrentSaveFile(SaveFile);
		static void ResetSaveFile(SaveFile);
		static void SetCurrentLocation(int key);
		static void SetAteTrash(bool);
		static void SetAtHouse(bool);
		static void SetStartedGame(bool);
		static bool AteTrash();
		static void InitSaveFiles();
		static bool StartedGame();
		static SaveFile GetCurrentSaveFile();
		static int GetCurrentLocationKey();
		static std::vector<SaveFile>& GetSaveFiles();
		static void DeleteSaveAtIndex(int index);
	private:
		static void ClearSaveFiles();

		static std::vector<SaveFile> saveFiles;
		static const int ADDRESS_CURRENT_LOCATION = 0x00000000;

		static const int ADDRESS_STARTED_GAME = 0x0000000F;
		static const int FLAG_POS_STARTED_GAME = 0;

		static const int ADDRESS_ATE_TRASH = 0x000000FF;
		static const int FLAG_POS_ATE_TRASH = 0;

		static const std::string SAVE_DEFAULT_DIRECTORY;
		static const std::string SAVE_DEFAULT_EXTENSION;
		static const std::string SAVE_CURRENT_NAME;
};


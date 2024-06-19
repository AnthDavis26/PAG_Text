#include "LocationKeys.h"
#include "SaveManager.h"
#include "Strings.h"

std::vector<SaveFile> SaveManager::saveFiles;
SaveFile SaveManager::currentSaveFile = SaveFile(Strings::SAVE_DEFAULT_DIRECTORY,
    Strings::SAVE_CURRENT_NAME,
    Strings::SAVE_DEFAULT_EXTENSION);
int SaveManager::ADDRESS_CURRENT_LOCATION = 0x00000000;
int SaveManager::ADDRESS_STARTED_GAME = 0x0000000F;
int SaveManager::FLAG_POS_STARTED_GAME = 0;
int SaveManager::ADDRESS_ATE_HOUSE_TRASH = 0x000000FF;
int SaveManager::FLAG_POS_ATE_HOUSE_TRASH = 0;

// TODO: implement
void SaveManager::DEBUG_CheckAllOverlaps() {
    // Implementation
}

const SaveFile& SaveManager::GetCurrentSaveFile() {
    return SaveManager::currentSaveFile;
}

int SaveManager::GetCurrentLocationKey() {
    return SaveManager::currentSaveFile.GetByteAt(SaveManager::ADDRESS_CURRENT_LOCATION);
}

void SaveManager::SetCurrentLocation(int locationKey) {
    SaveManager::currentSaveFile.SetByteAt(locationKey, SaveManager::ADDRESS_CURRENT_LOCATION);
}

void SaveManager::SetAtMainMenu() {
    SaveManager::SetCurrentLocation(LocationKeys::MAIN_MENU);
}

void SaveManager::SetAtPauseMenu() {
    SaveManager::SetCurrentLocation(LocationKeys::PAUSE_MENU);
}

void SaveManager::CreateNewFile(const SaveFile& sf) {
    size_t n = SaveManager::saveFiles.size();

    for (size_t i = 0; i < n; i++) {
        if (sf.GetFullPath() == SaveManager::saveFiles[i].GetFullPath()) {
            SaveManager::DeleteSaveAtIndex(static_cast<int>(i));
            break;
        }
    }

    std::ifstream fileSource(SaveManager::currentSaveFile.GetFullPath(), std::ios::binary);
    std::ofstream fileDestination(sf.GetFullPath(), std::ios::binary);
    SaveManager::saveFiles.push_back(sf);
    SaveManager::SortFiles();
}

void SaveManager::SortFiles() {
    std::sort(SaveManager::saveFiles.begin(), SaveManager::saveFiles.end());
}

void SaveManager::OverwriteSaveFile(const SaveFile& source, const SaveFile& destination) {
    std::ifstream fileSource(source.GetFullPath(), std::ios::binary);
    std::ofstream fileDestination(destination.GetFullPath(), std::ios::binary);

    if (!fileSource.is_open() || !fileDestination.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    fileDestination << fileSource.rdbuf();
}

void SaveManager::OverwriteCurrentSaveFile(const SaveFile& sf) {
    if (sf.GetFullPath() == SaveManager::currentSaveFile.GetFullPath()) {
        return;
    }

    SaveManager::OverwriteSaveFile(SaveManager::currentSaveFile, sf);
}

void SaveManager::SetAteHouseKitchenTrash() {
    SaveManager::currentSaveFile.SetBitAt(
        SaveManager::FLAG_POS_ATE_HOUSE_TRASH, SaveManager::ADDRESS_ATE_HOUSE_TRASH);
}

void SaveManager::SetAtDiner() {
    SaveManager::SetCurrentLocation(LocationKeys::DINER);
}

void SaveManager::SetStartedGame() {
    SaveManager::currentSaveFile.SetBitAt(
        SaveManager::FLAG_POS_STARTED_GAME, SaveManager::ADDRESS_STARTED_GAME);
}

bool SaveManager::AteHouseKitchenTrash() {
    return SaveManager::currentSaveFile.GetBitAt(
        SaveManager::FLAG_POS_ATE_HOUSE_TRASH, SaveManager::ADDRESS_ATE_HOUSE_TRASH);
}

void SaveManager::InitSaveFiles() {
    std::filesystem::create_directories(Strings::SAVE_DEFAULT_DIRECTORY);
    SaveManager::ClearSaveFiles();
    bool currentFileFound = false;

    for (const auto& entry : std::filesystem::directory_iterator(Strings::SAVE_DEFAULT_DIRECTORY)) {
        if (entry.path().extension() == Strings::SAVE_DEFAULT_EXTENSION) {
            std::string fileName = entry.path().filename().string();
            fileName = fileName.substr(0, fileName.size() - Strings::SAVE_DEFAULT_EXTENSION.size());

            if (fileName == Strings::SAVE_CURRENT_NAME) {
                currentFileFound = true;
            }
            else {
                SaveManager::saveFiles.push_back(SaveFile(Strings::SAVE_DEFAULT_DIRECTORY, fileName,
                    Strings::SAVE_DEFAULT_EXTENSION));
            }
        }
    }

    if (!currentFileFound) {
        SaveFile temp(Strings::SAVE_DEFAULT_DIRECTORY, Strings::SAVE_CURRENT_NAME,
            Strings::SAVE_DEFAULT_EXTENSION);
        temp.Reset();
        SaveManager::OverwriteCurrentSaveFile(temp);
    }
}

bool SaveManager::StartedGame() {
    return SaveManager::currentSaveFile.GetBitAt(
        SaveManager::FLAG_POS_STARTED_GAME, SaveManager::ADDRESS_STARTED_GAME);
}

int SaveManager::IndexOf(const SaveFile& sf) {
    size_t n = SaveManager::saveFiles.size();

    for (size_t i = 0; i < n; i++) {
        if (sf.GetFullPath() == SaveManager::saveFiles[i].GetFullPath()) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

bool SaveManager::Contains(const SaveFile& sf) {
    for (const auto& saveFile : SaveManager::saveFiles) {
        if (saveFile.GetFullPath() == sf.GetFullPath()) {
            return true;
        }
    }

    return false;
}

const std::vector<SaveFile>& SaveManager::GetSaveFiles() {
    return saveFiles;
}

void SaveManager::DeleteSaveAtIndex(int index) {
    SaveFile sf = SaveManager::saveFiles.at(index);
    SaveManager::saveFiles.erase(SaveManager::saveFiles.begin() + index);
    std::filesystem::remove(sf.GetFullPath());
}

void SaveManager::ResetCurrentSaveFile() {
    SaveManager::currentSaveFile.Reset();
}

void SaveManager::ClearSaveFiles() {
    SaveManager::saveFiles.clear();
}

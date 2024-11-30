#include "LocationKeys.h"
#include "SaveManager.h"
#include "Strings.h"
#include "Prompter.h"

std::vector<SaveFile> SaveManager::saveFiles;

SaveFile SaveManager::currentSaveFile = SaveFile(
    Strings::SAVE_DEFAULT_DIRECTORY,
    Strings::SAVE_CURRENT_NAME,
    Strings::SAVE_DEFAULT_EXTENSION);

int SaveManager::ADDRESS_CURRENT_LOCATION = 0x00000000;

int SaveManager::ADDRESS_STARTED_GAME = 0x00000001;
int SaveManager::FLAG_POS_STARTED_GAME = 0;

int SaveManager::ADDRESS_ATE_HOUSE_TRASH = 0x00000002;
int SaveManager::FLAG_POS_ATE_HOUSE_TRASH = 0;

int SaveManager::ADDRESS_KILLED_DINER_OWNER = 0x00000003;
int SaveManager::FLAG_POS_KILLED_DINER_OWNER = 0;
int SaveManager::FLAG_POS_KILLED_DINER_OWNER_THEN_LEFT = 1;

void SaveManager::DEBUG_CheckAllOverlaps() {
    std::string errorOutput = "";
    SaveFile dbSave(Strings::SAVE_DEFAULT_DIRECTORY, "DEBUG", Strings::SAVE_DEFAULT_EXTENSION);
    SaveManager::CreateNewFile(dbSave);
    dbSave.Reset();

    // Current Location
    if (dbSave.GetByteAt(ADDRESS_CURRENT_LOCATION)) {
        errorOutput += "OVERLAP AT ADDRESS_CURRENT_LOCATION!\n";
    } dbSave.SetBitAt(0, ADDRESS_CURRENT_LOCATION);

    // Started Game
    if (dbSave.GetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME)) {
        errorOutput += "OVERLAP AT ADDRESS_STARTED_GAME AT FLAG_POS_STARTED_GAME!\n";
    } dbSave.SetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);

    // Ate House Trash
    if (dbSave.GetBitAt(FLAG_POS_ATE_HOUSE_TRASH, ADDRESS_ATE_HOUSE_TRASH)) {
        errorOutput += "OVERLAP AT ADDRESS_ATE_HOUSE_TRASH AT FLAG_POS_ATE_HOUSE_TRASH!\n";
    } dbSave.SetBitAt(FLAG_POS_ATE_HOUSE_TRASH, ADDRESS_ATE_HOUSE_TRASH);

    // Killed Diner Owner
    if (dbSave.GetBitAt(FLAG_POS_KILLED_DINER_OWNER, ADDRESS_KILLED_DINER_OWNER)) {
        errorOutput += "OVERLAP AT ADDRESS_KILLED_DINER_OWNER! AT POS FLAG_POS_KILLED_DINER_OWNER\n";
    }  dbSave.SetBitAt(FLAG_POS_KILLED_DINER_OWNER, ADDRESS_KILLED_DINER_OWNER);

    // Killed Diner Owner Then Left
    if (dbSave.GetBitAt(FLAG_POS_KILLED_DINER_OWNER_THEN_LEFT, ADDRESS_KILLED_DINER_OWNER)) {
        errorOutput += "OVERLAP AT ADDRESS_KILLED_DINER_OWNER! AT POS FLAG_POS_KILLED_DINER_OWNER_THEN_LEFT\n";
    } dbSave.SetBitAt(FLAG_POS_KILLED_DINER_OWNER_THEN_LEFT, ADDRESS_KILLED_DINER_OWNER);

    SaveManager::DeleteSaveAtIndex(SaveManager::IndexOf(dbSave));

    if (!errorOutput.empty()) {
        Prompter::Print(errorOutput);
    }
}

bool SaveManager::AteHouseKitchenTrash() {
    return SaveManager::GetCurrentSaveFile().GetBitAt(
        SaveManager::FLAG_POS_ATE_HOUSE_TRASH, SaveManager::ADDRESS_ATE_HOUSE_TRASH);
}

bool SaveManager::KilledDinerOwner() {
    return SaveManager::GetCurrentSaveFile().GetBitAt(
        SaveManager::FLAG_POS_KILLED_DINER_OWNER, SaveManager::ADDRESS_KILLED_DINER_OWNER);
}

bool SaveManager::KilledDinerOwnerThenLeft() {
    return SaveManager::GetCurrentSaveFile().GetBitAt(
        SaveManager::FLAG_POS_KILLED_DINER_OWNER_THEN_LEFT, SaveManager::ADDRESS_KILLED_DINER_OWNER);
}

SaveFile& SaveManager::GetCurrentSaveFile() {
    return SaveManager::currentSaveFile;
}

int SaveManager::GetCurrentLocationKey() {
    return SaveManager::GetCurrentSaveFile().GetByteAt(SaveManager::ADDRESS_CURRENT_LOCATION);
}

void SaveManager::SetCurrentLocation(int locationKey) {
    SaveManager::GetCurrentSaveFile().SetByteAt(locationKey, SaveManager::ADDRESS_CURRENT_LOCATION);
}

void SaveManager::SetAtMainMenu() {
    SaveManager::SetCurrentLocation(LocationKeys::MAIN_MENU);
}

void SaveManager::SetAtPauseMenu() {
    SaveManager::SetCurrentLocation(LocationKeys::PAUSE_MENU);
}

void SaveManager::CreateNewFile(const SaveFile& sf) {
    size_t n = SaveManager::GetSaveFiles().size();

    for (size_t i = 0; i < n; i++) {
        if (sf.GetFullPath() == SaveManager::GetSaveFiles()[i].GetFullPath()) {
            SaveManager::DeleteSaveAtIndex(static_cast<int>(i));
            break;
        }
    }

    std::ifstream fileSource(SaveManager::GetCurrentSaveFile().GetFullPath(), std::ios::binary);
    std::ofstream fileDestination(sf.GetFullPath(), std::ios::binary);
    SaveManager::GetSaveFiles().push_back(sf);
    SaveManager::SortFiles();
}

void SaveManager::SortFiles() {
    std::sort(SaveManager::GetSaveFiles().begin(), SaveManager::GetSaveFiles().end());
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
    if (sf.GetFullPath() == SaveManager::GetCurrentSaveFile().GetFullPath()) {
        return;
    }

    SaveManager::OverwriteSaveFile(SaveManager::GetCurrentSaveFile(), sf);
}

void SaveManager::SetAteHouseKitchenTrash() {
    SaveManager::GetCurrentSaveFile().SetBitAt(
        SaveManager::FLAG_POS_ATE_HOUSE_TRASH, SaveManager::ADDRESS_ATE_HOUSE_TRASH);
}

void SaveManager::SetKilledDinerOwner(bool b) {
    if (b) {
        SaveManager::GetCurrentSaveFile().SetBitAt(
            SaveManager::FLAG_POS_KILLED_DINER_OWNER, SaveManager::ADDRESS_KILLED_DINER_OWNER);
    } else {
        SaveManager::GetCurrentSaveFile().UnsetBitAt(
            SaveManager::FLAG_POS_KILLED_DINER_OWNER, SaveManager::ADDRESS_KILLED_DINER_OWNER);
    }
}

void SaveManager::SetKilledDinerOwnerThenLeft(bool b) {
    if (b) {
        SaveManager::GetCurrentSaveFile().SetBitAt(
            SaveManager::FLAG_POS_KILLED_DINER_OWNER_THEN_LEFT, SaveManager::ADDRESS_KILLED_DINER_OWNER);
    } else {
        SaveManager::GetCurrentSaveFile().UnsetBitAt(
            SaveManager::FLAG_POS_KILLED_DINER_OWNER_THEN_LEFT, SaveManager::ADDRESS_KILLED_DINER_OWNER);
    }
}

void SaveManager::SetAtHouse() {
    SaveManager::SetCurrentLocation(LocationKeys::HOUSE_LIVING_ROOM);
}

void SaveManager::SetAtDiner() {
    SaveManager::SetCurrentLocation(LocationKeys::DINER);
}

void SaveManager::SetStartedGame() {
    SaveManager::GetCurrentSaveFile().SetBitAt(
        SaveManager::FLAG_POS_STARTED_GAME, SaveManager::ADDRESS_STARTED_GAME);
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
            } else {
                SaveManager::GetSaveFiles().push_back(SaveFile(Strings::SAVE_DEFAULT_DIRECTORY, fileName,
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
    return SaveManager::GetCurrentSaveFile().GetBitAt(
        SaveManager::FLAG_POS_STARTED_GAME, SaveManager::ADDRESS_STARTED_GAME);
}

int SaveManager::IndexOf(const SaveFile& sf) {
    size_t n = SaveManager::GetSaveFiles().size();

    for (size_t i = 0; i < n; i++) {
        if (sf.GetFullPath() == SaveManager::GetSaveFiles()[i].GetFullPath()) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

bool SaveManager::Contains(const SaveFile& sf) {
    for (const auto& saveFile : SaveManager::GetSaveFiles()) {
        if (saveFile.GetFullPath() == sf.GetFullPath()) {
            return true;
        }
    }

    return false;
}

std::vector<SaveFile>& SaveManager::GetSaveFiles() {
    return saveFiles;
}

void SaveManager::DeleteSaveAtIndex(int index) {
    SaveFile sf = SaveManager::GetSaveFiles()[index];
    SaveManager::GetSaveFiles().erase(SaveManager::GetSaveFiles().begin() + index);
    std::filesystem::remove(sf.GetFullPath());
}

void SaveManager::ResetCurrentSaveFile() {
    SaveManager::GetCurrentSaveFile().Reset();
}

void SaveManager::ClearSaveFiles() {
    SaveManager::GetSaveFiles().clear();
}

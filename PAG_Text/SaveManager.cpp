#include "SaveManager.h"
#include "LocationKeys.h"

std::vector<SaveFile> SaveManager::saveFiles;
const std::string SaveManager::SAVE_DEFAULT_DIRECTORY = "./Saves/";
const std::string SaveManager::SAVE_CURRENT_NAME = "~CURRENT";
const std::string SaveManager::SAVE_DEFAULT_EXTENSION = ".sav";

// TODO: implement
void SaveManager::DEBUG_CheckAllOverlaps() {
    // Create blank test save file
    // As you set bits, make sure one hasn't already been set
    // If overlap is found, print "ERROR: Save Overlap at: " + overlap bit address
    //      " during operation: " + some_operation(such as ate trash?)
    // Otherwise, print "Overlap Check GOOD"
}

SaveFile SaveManager::GetCurrentSaveFile() {
    return SaveFile(SaveManager::SAVE_DEFAULT_DIRECTORY, 
        SaveManager::SAVE_CURRENT_NAME, SaveManager::SAVE_DEFAULT_EXTENSION);
}

int SaveManager::GetCurrentLocationKey() {
    return SaveManager::GetCurrentSaveFile().GetByteAt(ADDRESS_CURRENT_LOCATION);
}

void SaveManager::SetCurrentLocation(int locationKey) {
    SaveManager::GetCurrentSaveFile().SetByteAt(locationKey, ADDRESS_CURRENT_LOCATION);
}

void SaveManager::SetAtMainMenu() {
    SaveManager::SetCurrentLocation(LocationKeys::MAIN_MENU);
}

void SaveManager::SetAtPauseMenu() {
    SaveManager::SetCurrentLocation(LocationKeys::PAUSE_MENU);
}

void SaveManager::CreateNewFile(SaveFile sf) {
    for (int i = 0; i < SaveManager::GetSaveFiles().size(); i++) {
        if (sf.GetFullPath() == SaveManager::GetSaveFiles()[i].GetFullPath()) {
            SaveManager::DeleteSaveAtIndex(i);
            break;
        }
    }

    std::ifstream fileSource(SaveManager::GetCurrentSaveFile().GetFullPath(), std::ios::binary);
    std::ofstream fileDestination(sf.GetFullPath(), std::ios::binary);

    std::cout << sf.GetFullPath() << std::endl;
    SaveManager::GetSaveFiles().push_back(sf);
    SaveManager::SortFiles();
}

void SaveManager::SortFiles() {
    std::sort(SaveManager::GetSaveFiles().begin(), SaveManager::GetSaveFiles().end());
}

void SaveManager::OverwriteSaveFile(SaveFile source, SaveFile destination) {
    std::ifstream fileSource(source.GetFullPath(), std::ios::binary);
    std::ofstream fileDestination(destination.GetFullPath(), std::ios::binary);

    if (!fileSource.is_open() || !fileDestination.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    fileDestination << fileSource.rdbuf();
    fileSource.close();
    fileDestination.close();
}

void SaveManager::OverwriteCurrentSaveFileWith(SaveFile sf) {
    // Don't replace current save file with itself
    if (sf.GetFullPath() == SaveManager::GetCurrentSaveFile().GetFullPath()) {
        return;
    }

    SaveManager::OverwriteSaveFile(SaveManager::GetCurrentSaveFile(), sf);
}

void SaveManager::SetAteHouseTrash() {
    SaveManager::GetCurrentSaveFile().SetBitAt(FLAG_POS_ATE_HOUSE_TRASH, ADDRESS_ATE_HOUSE_TRASH);
}

void SaveManager::SetAtHouse() {
    SaveManager::SetCurrentLocation(LocationKeys::HOUSE);
}

void SaveManager::SetAtDiner() {
    SaveManager::SetCurrentLocation(LocationKeys::DINER);
}

void SaveManager::SetStartedGame() {
    SaveManager::GetCurrentSaveFile().SetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);
}

bool SaveManager::AteTrash() {
    return GetCurrentSaveFile().GetBitAt(FLAG_POS_ATE_HOUSE_TRASH, ADDRESS_ATE_HOUSE_TRASH);
}

void SaveManager::InitSaveFiles() {
    SaveManager::ClearSaveFiles();
    bool currentFileFound = false;

    // Search for and add list of files with correct extension
    for (const auto& entry : std::filesystem::directory_iterator(SaveManager::SAVE_DEFAULT_DIRECTORY)) {
        if (entry.path().extension() == SAVE_DEFAULT_EXTENSION) {
            std::string fileName = entry.path().filename().string();
            fileName = fileName.substr(0, fileName.size() - SAVE_DEFAULT_EXTENSION.size());

            if (fileName == SaveManager::SAVE_CURRENT_NAME) {
                currentFileFound = true;
            } else {
                SaveManager::GetSaveFiles().push_back(SaveFile(SaveManager::SAVE_DEFAULT_DIRECTORY, fileName, SAVE_DEFAULT_EXTENSION));
            }
        }
    }

    if (!currentFileFound) {
        SaveFile temp(SaveManager::SAVE_DEFAULT_DIRECTORY, SaveManager::SAVE_CURRENT_NAME, SAVE_DEFAULT_EXTENSION);
        temp.Reset();
        SaveManager::OverwriteCurrentSaveFileWith(temp);
    }
}

bool SaveManager::StartedGame() {
    return SaveManager::GetCurrentSaveFile().GetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);
}

int SaveManager::IndexOf(SaveFile sf) {
    for (int i = 0; i < SaveManager::GetSaveFiles().size(); i++) {
        if (sf.GetFullPath() == SaveManager::GetSaveFiles().at(i).GetFullPath()) {
            return i;
        }
    }

    return -1;
}

bool SaveManager::Contains(SaveFile sf) {
    for (SaveFile saveFile : SaveManager::GetSaveFiles()) {
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
    SaveFile sf = SaveManager::GetSaveFiles().at(index);
    SaveManager::GetSaveFiles().erase(SaveManager::GetSaveFiles().begin() + index);
    std::filesystem::remove(sf.GetFullPath());
}

void SaveManager::ClearSaveFiles() {
    SaveManager::GetSaveFiles().clear();
}

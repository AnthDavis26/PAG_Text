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

void SaveManager::SetCurrentLocation(int key) {
    SaveManager::GetCurrentSaveFile().SetByteAt(key, ADDRESS_CURRENT_LOCATION);
}

void SaveManager::OverwriteCurrentSaveFile(SaveFile sf) {
    if (sf.GetFullPath() == SaveManager::GetCurrentSaveFile().GetFullPath()) {
        return;
    }

    std::ifstream source(sf.GetFullPath(), std::ios::binary);
    std::ofstream dest(SaveManager::GetCurrentSaveFile().GetFullPath(), std::ios::binary);

    if (!source.is_open() || !dest.is_open()) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }

    dest << source.rdbuf();

    source.close();
    dest.close();
}

void SaveManager::ResetSaveFile(SaveFile sf) {

}

void SaveManager::SetAteTrash(bool b) {
    if (b) {
        SaveManager::GetCurrentSaveFile().SetBitAt(FLAG_POS_ATE_TRASH, ADDRESS_ATE_TRASH);
    }
    else {
        SaveManager::GetCurrentSaveFile().UnsetBitAt(FLAG_POS_ATE_TRASH, ADDRESS_ATE_TRASH);
    }
}

void SaveManager::SetAtHouse(bool) {
    SaveManager::SetCurrentLocation(LocationKeys::HOUSE);
}

void SaveManager::SetStartedGame(bool b) {
    if (b) {
        SaveManager::GetCurrentSaveFile().SetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);
    }
    else {
        SaveManager::GetCurrentSaveFile().UnsetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);
    }
}

bool SaveManager::AteTrash() {
    return GetCurrentSaveFile().GetBitAt(FLAG_POS_ATE_TRASH, ADDRESS_ATE_TRASH);
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
        SaveManager::OverwriteCurrentSaveFile(temp);
    }
}

bool SaveManager::StartedGame() {
    return SaveManager::GetCurrentSaveFile().GetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);
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

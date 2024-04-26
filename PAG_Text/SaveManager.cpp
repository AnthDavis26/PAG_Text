#include "SaveManager.h"
#include "LocationKeys.h"

std::vector<SaveFile> SaveManager::saveFiles;

// TODO: implement
void SaveManager::DEBUG_CheckAllOverlaps()
{
    // Create blank test save file
    // As you set bits, make sure one hasn't already been set
    // If overlap is found, print "ERROR: Save Overlap at: " + overlap bit address
    //      " during operation: " + some_operation(such as ate trash?)
    // Otherwise, print "Overlap Check GOOD"
}

SaveFile SaveManager::GetCurrentSaveFile()
{
    return SaveFile(Save::DIRECTORY, Save::NAME_DEFAULT);
}

int SaveManager::GetCurrentLocationKey()
{
    return SaveManager::GetCurrentSaveFile().GetByteAt(ADDRESS_CURRENT_LOCATION);
}

void SaveManager::SetCurrentLocation(int key)
{
    SaveManager::GetCurrentSaveFile().SetByteAt(key, ADDRESS_CURRENT_LOCATION);
}

void SaveManager::OverwriteCurrentSaveFile(SaveFile sf)
{
    if (sf.GetFullPath() == GetCurrentSaveFile().GetFullPath()) {
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

void SaveManager::SetAteTrash(bool b)
{
    if (b) {
        SaveManager::GetCurrentSaveFile().SetBitAt(FLAG_POS_ATE_TRASH, ADDRESS_ATE_TRASH);
    }
    else {
        SaveManager::GetCurrentSaveFile().UnsetBitAt(FLAG_POS_ATE_TRASH, ADDRESS_ATE_TRASH);
    }
}

void SaveManager::SetAtHouse(bool)
{
    SaveManager::SetCurrentLocation(LocationKeys::KEY_LOC_HOUSE);
}

void SaveManager::SetStartedGame(bool b)
{
    if (b) {
        SaveManager::GetCurrentSaveFile().SetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);
    }
    else {
        SaveManager::GetCurrentSaveFile().UnsetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);
    }
}

bool SaveManager::AteTrash()
{
    return GetCurrentSaveFile().GetBitAt(FLAG_POS_ATE_TRASH, ADDRESS_ATE_TRASH);
}

void SaveManager::InitSaveFiles() {
    bool currentFileFound = false;

    // Search for and add list of files with correct extension
    for (const auto& entry : std::filesystem::directory_iterator(Save::DIRECTORY)) {
        if (entry.path().extension() == Save::EXTENSION) {
            std::string fileName = entry.path().filename().string();
            fileName = fileName.substr(0, fileName.size() - Save::EXTENSION.size());

            if (fileName == Save::NAME_DEFAULT) {
                currentFileFound = true;
            } else {
                SaveManager::GetSaveFiles().push_back(SaveFile(Save::DIRECTORY, fileName));
            }
        }
    }

    if (!currentFileFound) {
        SaveFile temp(Save::DIRECTORY, Save::NAME_DEFAULT);
        temp.Reset();
        SaveManager::OverwriteCurrentSaveFile(temp);
    }
}

bool SaveManager::StartedGame()
{
    return SaveManager::GetCurrentSaveFile().GetBitAt(FLAG_POS_STARTED_GAME, ADDRESS_STARTED_GAME);
}


std::vector<SaveFile>& SaveManager::GetSaveFiles()
{
    return saveFiles;
}

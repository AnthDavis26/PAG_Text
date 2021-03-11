#include <iostream>
#include <filesystem>
#include <fstream>
#include "SaveFileInterface.h"

const std::string S_SAVE_PATH = ".\\Saves\\";
const std::string S_SAVE_FILE = "SAV";

// Prototypes
void InitFiles();

int main()
{
    InitFiles();

    SaveFileInterface sfi;

    // Create a test save file
    sfi.SetByteAt(S_SAVE_PATH, S_SAVE_FILE, 0xAB, 0x23);
    sfi.OrByteAt(S_SAVE_PATH, S_SAVE_FILE, 0x13, 0x23);
    sfi.OrByteAt(S_SAVE_PATH, S_SAVE_FILE, 0x02, 0x1A);
    sfi.ANDByteAt(S_SAVE_PATH, S_SAVE_FILE, 0x07, 0x23);
}


void InitFiles()
{
    std::ofstream file;

    if (!std::filesystem::exists(S_SAVE_PATH))
        std::filesystem::create_directory(S_SAVE_PATH);

    if (!std::filesystem::exists(S_SAVE_PATH + S_SAVE_FILE))
    {
        file.open(S_SAVE_PATH + S_SAVE_FILE, std::ios::out | std::ios::binary);
        file.close();
    }
}

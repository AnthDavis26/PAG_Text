#include <iostream>
#include <filesystem>
#include <fstream>

const std::string S_SAVE_PATH = ".\\Saves\\";
const std::string S_SAVE_FILE = "SAV";

// Prototypes
void SetByteAt(std::string path, std::string filename, int byte, int addr);
void InitFiles();

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

// byte range [0, 255]
void SetByteAt(std::string path, std::string filename, int byte, int addr)
{
    std::ofstream file;
    path += filename;

    if (std::filesystem::exists(path))
        file.open(path, std::ios::in | std::ios::out | std::ios::binary);
    else
        file.open(path, std::ios::out | std::ios::binary);

    file.seekp(addr);
    file.put(byte);

    file.close();
}

int main()
{
    InitFiles();

    // Create a test save file
    SetByteAt(S_SAVE_PATH, S_SAVE_FILE, 0xAF, 0x23);
}

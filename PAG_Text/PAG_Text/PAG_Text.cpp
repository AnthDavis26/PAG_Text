#include <iostream>
#include <filesystem>
#include <fstream>

const std::string SAVE_PATH = ".\\Saves\\";

// Prototypes
void SetByteAt(std::string fullpath, int byte, int addr);

void SetByteAt(std::string fullpath, int byte, int addr)
{
    // Read and write out to file
    std::ofstream file(fullpath, std::ios::in | std::ios::out | std::ios::binary);

    file.seekp(addr);
    file.put(byte);

    file.close();
}

int main()
{
    // Create a test save file
    SetByteAt(SAVE_PATH + "SAV", 3, 0x022);
}

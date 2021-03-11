#include "SaveFileInterface.h"
#include <filesystem>
#include <fstream>

// byte range [0, 255]
void SaveFileInterface::SetByteAt(std::string path, std::string filename, int byte, int addr)
{
    std::fstream file;
    Helper_CheckFile(path+filename, file);
    Helper_PlaceByte(file, byte, addr);
    file.close();
}

void SaveFileInterface::OrByteAt(std::string path, std::string filename, int byte, int addr)
{
    std::fstream file;
    Helper_CheckFile(path+filename, file);

    file.seekg(addr);
    byte |= file.get();

    Helper_PlaceByte(file, byte, addr);
    file.close();
}

void SaveFileInterface::ANDByteAt(std::string path, std::string filename, int byte, int addr)
{
    std::fstream file;
    Helper_CheckFile(path + filename, file);

    file.seekg(addr);
    byte &= file.get();

    Helper_PlaceByte(file, byte, addr);
    file.close();
}

void SaveFileInterface::Helper_CheckFile(std::string fullpath, std::fstream &file)
{
    // Modify file if it exists, otherwise create file
    if (std::filesystem::exists(fullpath))
        file.open(fullpath, std::ios::in | std::ios::out | std::ios::binary);
    else
        file.open(fullpath, std::ios::out | std::ios::binary);
}

void SaveFileInterface::Helper_PlaceByte(std::fstream& file, int byte, int addr)
{
    file.seekp(addr);
    file.put(byte);
}

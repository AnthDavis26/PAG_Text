#include "SaveFile.h"
#include <filesystem>

SaveFile::SaveFile(std::string directory, std::string fileName)
{
    this->directory = directory;
    this->fileName = fileName;
    this->fullPath = directory + fileName;

    OpenFile();
    file.close();
}

std::string SaveFile::GetFullPath()
{
    return fullPath;
}

std::string SaveFile::GetDirectory()
{
    return directory;
}


// byte range [0, 255]
void SaveFile::SetByteAt(int byte, int addr)
{
    OpenFile();
    file.seekp(addr);
    file.put(byte);
    file.close();
}

void SaveFile::ORByteAt(int byte, int addr)
{
    OpenFile();

    if (addr > std::filesystem::file_size(fullPath))
        std::filesystem::resize_file(fullPath, addr);
    else
    {
        file.seekg(addr);
        byte |= file.get();
    }

    file.seekp(addr);
    file.put(byte);
    file.close();
}

void SaveFile::ANDByteAt(int byte, int addr)
{
    OpenFile();
    if (addr > std::filesystem::file_size(fullPath))
        std::filesystem::resize_file(fullPath, addr);
    else
    {
        file.seekg(addr);
        byte &= file.get();
        file.seekp(addr);
        file.put(byte);
    }

    file.close();
}

void SaveFile::SetBitAt(int bitpos, int addr)
{
    ORByteAt((1 << bitpos), addr);
}

void SaveFile::UnsetBitAt(int bitpos, int addr)
{
    ANDByteAt(~(1 << bitpos), addr);
}

void SaveFile::Reset()
{
    if (!std::filesystem::exists(fullPath))
        std::filesystem::create_directory(directory);
    
    file.open(fullPath, std::ios::out | std::ios::binary);
    file.close();
}

void SaveFile::OpenFile()
{
    // Modify file if it exists, otherwise create file
    if (std::filesystem::exists(fullPath))
        file.open(fullPath, std::ios::in | std::ios::out | std::ios::binary);
    else
    {
        std::filesystem::create_directory(directory);
        file.open(fullPath, std::ios::out | std::ios::binary);
    }
}

std::ostream& operator<<(std::ostream& os, const SaveFile& sf)
{
    os << sf.fullPath;
    return os;
}

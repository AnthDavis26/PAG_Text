#include "SaveFile.h"
#include <filesystem>

SaveFile::SaveFile(std::string directory, std::string filename)
{
    this->directory = directory;
    this->filename = filename;
    this->fullpath = directory + filename;

    OpenFile();
    file.close();
}

std::string SaveFile::GetFullPath()
{
    return fullpath;
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

    if (addr > std::filesystem::file_size(fullpath))
        std::filesystem::resize_file(fullpath, addr);
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
    if (addr > std::filesystem::file_size(fullpath))
        std::filesystem::resize_file(fullpath, addr);
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
    if (!std::filesystem::exists(fullpath))
        std::filesystem::create_directory(directory);
    
    file.open(fullpath, std::ios::out | std::ios::binary);
    file.close();
}

void SaveFile::OpenFile()
{
    // Modify file if it exists, otherwise create file
    if (std::filesystem::exists(fullpath))
        file.open(fullpath, std::ios::in | std::ios::out | std::ios::binary);
    else
    {
        std::filesystem::create_directory(directory);
        file.open(fullpath, std::ios::out | std::ios::binary);
    }
}

std::ostream& operator<<(std::ostream& os, const SaveFile& sf)
{
    os << sf.fullpath;
    return os;
}

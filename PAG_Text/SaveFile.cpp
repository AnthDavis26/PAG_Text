#include "SaveFile.h"
#include <filesystem>
#include "Save.h"

SaveFile::SaveFile()
{
    SetDirectory(Save::DIRECTORY);
    SetFileName("blank");
}

SaveFile::SaveFile(SaveFile const& sf)
{
    SetDirectory(sf.GetDirectory());
    SetFileName(sf.GetFileName());
}

SaveFile::SaveFile(std::string directory)
{
    SetDirectory(directory);
    SetFileName("blank");
}

SaveFile::SaveFile(std::string directory, std::string fileName)
{
    SetDirectory(directory);
    SetFileName(fileName);
}


SaveFile& SaveFile::operator=(const SaveFile& sf)
{
    SetDirectory(sf.GetDirectory());
    SetFileName(sf.GetFileName());
    return *this;
}

std::string SaveFile::GetDirectory() const
{
    return directory;
}

std::string SaveFile::GetFullPath() const
{
    return GetDirectory() + GetFileName() + Save::EXTENSION;
}

int SaveFile::GetBitAt(int pos, int addr)
{
    return (GetByteAt(addr) >> pos) & 1;
}

int SaveFile::GetByteAt(int addr)
{
    OpenFile();
    GetFile().seekg(addr);
    int byte = GetFile().get();
    GetFile().close();

    return byte;
}

std::fstream& SaveFile::GetFile()
{
    return file;
}

std::string SaveFile::GetFileName() const
{
    return fileName;
}

// byte range [0, 255]
void SaveFile::SetByteAt(int byte, int addr)
{
    OpenFile();
    GetFile().seekp(addr);
    GetFile().put(byte);
    GetFile().close();
}

void SaveFile::ORByteAt(int byte, int addr)
{
    OpenFile();

    if (addr > std::filesystem::file_size(GetFullPath()))
        std::filesystem::resize_file(GetFullPath(), addr);
    else
    {
        GetFile().seekg(addr);
        byte |= GetFile().get();
    }

    GetFile().seekp(addr);
    GetFile().put(byte);
    GetFile().close();
}

void SaveFile::ANDByteAt(int byte, int addr)
{
    OpenFile();

    if (addr > std::filesystem::file_size(GetFullPath()))
        std::filesystem::resize_file(GetFullPath(), addr);
    else
    {
        GetFile().seekg(addr);
        byte &= file.get();
        GetFile().seekp(addr);
        GetFile().put(byte);
    }

    GetFile().close();
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
    std::ofstream file(GetFullPath(), std::ios::binary);

    const int numZeros = 1000;

    // Write zeros to the file
    for (int i = 0; i < numZeros; ++i) {
        file.put(0);
    }

    file.close();
}

void SaveFile::SetDirectory(std::string directory)
{
    this->directory = directory;
}

void SaveFile::SetFileName(std::string fileName)
{
    this->fileName = fileName;
}

void SaveFile::OpenFile() {
    // Modify file if it exists, otherwise create file
    if (std::filesystem::exists(GetFullPath())) {
        GetFile().open(GetFullPath(), std::ios::in | std::ios::out | std::ios::binary);
    }
    else {
        std::filesystem::create_directories(directory);
        GetFile().open(GetFullPath(), std::ios::out | std::ios::binary);
    }
}



static std::ostream& operator<<(std::ostream& os, const SaveFile& sf)
{
    os << sf.GetFullPath();
    return os;
}




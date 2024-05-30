#include "SaveFile.h"
#include <filesystem>

SaveFile::SaveFile() {
    SaveFile::SetDirectory("");
    SaveFile::SetFileName("");
    SaveFile::SetExtension("");
}

SaveFile::SaveFile(const SaveFile& sf) {
    SaveFile::SetDirectory(sf.GetDirectory());
    SaveFile::SetFileName(sf.GetFileName());
    SaveFile::SetExtension(sf.GetExtension());
}

SaveFile::SaveFile(std::string directory, std::string fileName, std::string extension) {
    SaveFile::SetDirectory(directory);
    SaveFile::SetFileName(fileName);
    SaveFile::SetExtension(extension);
}

SaveFile& SaveFile::operator=(const SaveFile& sf) {
    SaveFile::SetDirectory(sf.GetDirectory());
    SaveFile::SetFileName(sf.GetFileName());
    SaveFile::SetExtension(sf.GetExtension());
    return *this;
}

bool SaveFile::operator<(const SaveFile& other) const {
    return this->GetFullPath() < other.GetFullPath();
}

std::string SaveFile::GetDirectory() const {
    return this->directory;
}

std::string SaveFile::GetFullPath() const {
    return SaveFile::GetDirectory() + SaveFile::GetFileName() + SaveFile::GetExtension();
}

int SaveFile::GetBitAt(int pos, int addr) {
    return (SaveFile::GetByteAt(addr) >> pos) & 1;
}

int SaveFile::GetByteAt(int addr) {
    SaveFile::OpenFile();
    SaveFile::GetFile().seekg(addr);
    int byte = SaveFile::GetFile().get();
    SaveFile::GetFile().close();

    return byte;
}

std::fstream& SaveFile::GetFile() {
    return this->file;
}

std::string SaveFile::GetFileName() const {
    return this->fileName;
}

std::string SaveFile::GetExtension() const {
    return this->extension;
}

// byte range [0, 255]
void SaveFile::SetByteAt(int byte, int addr) {
    SaveFile::OpenFile();
    SaveFile::GetFile().seekp(addr);
    SaveFile::GetFile().put(byte);
    SaveFile::GetFile().close();
}

void SaveFile::ORByteAt(int byte, int addr) {
    SaveFile::OpenFile();

    if (addr > std::filesystem::file_size(GetFullPath())) {
        std::filesystem::resize_file(GetFullPath(), addr);
    } else {
        SaveFile::GetFile().seekg(addr);
        byte |= SaveFile::GetFile().get();
    }

    SaveFile::GetFile().seekp(addr);
    SaveFile::GetFile().put(byte);
    SaveFile::GetFile().close();
}

void SaveFile::ANDByteAt(int byte, int addr) {
    SaveFile::OpenFile();

    if (addr > std::filesystem::file_size(GetFullPath())) {
        std::filesystem::resize_file(GetFullPath(), addr);
    } else {
        SaveFile::GetFile().seekg(addr);
        byte &= file.get();
        SaveFile::GetFile().seekp(addr);
        SaveFile::GetFile().put(byte);
    }

    SaveFile::GetFile().close();
}

void SaveFile::SetBitAt(int bitpos, int addr) {
    SaveFile::ORByteAt((1 << bitpos), addr);
}

void SaveFile::UnsetBitAt(int bitpos, int addr) {
    SaveFile::ANDByteAt(~(1 << bitpos), addr);
}

bool SaveFile::contentsEqualTo(SaveFile sf) {
    std::ifstream f1(SaveFile::GetFullPath(), std::ifstream::binary | std::ifstream::ate);
    std::ifstream f2(sf.GetFullPath(), std::ifstream::binary | std::ifstream::ate);

    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::istreambuf_iterator<char>(f2.rdbuf()));
}

void SaveFile::Reset() const {
    std::ofstream file(GetFullPath(), std::ios::binary);

    for (int i = 0; i < SaveFile::MAX_ADDRESSES; i++) {
        file.put(0);
    }

    file.close();
}

void SaveFile::SetDirectory(std::string directory) {
    this->directory = directory;
}

void SaveFile::SetFileName(std::string fileName) {
    this->fileName = fileName;
}

void SaveFile::SetExtension(std::string extension) {
    this->extension = extension;
}

void SaveFile::OpenFile() {
    if (std::filesystem::exists(GetFullPath())) {
        SaveFile::GetFile().open(SaveFile::GetFullPath(), std::ios::in | std::ios::out | std::ios::binary);
    } else {
        std::filesystem::create_directories(directory);
        SaveFile::GetFile().open(SaveFile::GetFullPath(), std::ios::out | std::ios::binary);
    }
}

static std::ostream& operator<<(std::ostream& os, const SaveFile& sf) {
    os << sf.GetFullPath();
    return os;
}
#include "SaveFile.h"
#include <filesystem>
#include <iterator>
#include <algorithm>

SaveFile::SaveFile()
    : directory(""), fileName(""), extension(""), file(std::make_unique<std::fstream>()) {}

SaveFile::SaveFile(const SaveFile& other)
    : directory(other.directory), fileName(other.fileName), extension(other.extension), file(std::make_unique<std::fstream>()) {}

SaveFile::SaveFile(const std::string& dir, const std::string& name, const std::string& ext)
    : directory(dir), fileName(name), extension(ext), 
    file(std::make_unique<std::fstream>()) {}

SaveFile& SaveFile::operator=(const SaveFile& other) {
    if (this == &other) {
        return *this;
    }

    SetDirectory(other.GetDirectory());
    SetFileName(other.GetFileName());
    SetExtension(other.GetExtension());

    std::ifstream source(other.GetFullPath(), std::ios::binary);
    if (!source.is_open()) {
        std::cerr << "Error: Unable to open source file: " << other.GetFullPath() << std::endl;
        return *this;
    }

    std::ofstream destination(GetFullPath(), std::ios::binary | std::ios::trunc);
    if (!destination.is_open()) {
        std::cerr << "Error: Unable to open destination file: " << GetFullPath() << std::endl;
        source.close();
        return *this;
    }

    destination << source.rdbuf();
    source.close();
    destination.close();

    return *this;
}


bool SaveFile::operator<(const SaveFile& other) const {
    return this->GetFullPath() < other.GetFullPath();
}

bool SaveFile::operator==(const SaveFile& other) const {
    std::ifstream f1(GetFullPath(), std::ifstream::binary | std::ifstream::ate);
    std::ifstream f2(other.GetFullPath(), std::ifstream::binary | std::ifstream::ate);

    f1.seekg(0, std::ifstream::beg);
    f2.seekg(0, std::ifstream::beg);
    return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
        std::istreambuf_iterator<char>(),
        std::istreambuf_iterator<char>(f2.rdbuf()));
}

const std::string& SaveFile::GetDirectory() const {
    return this->directory;
}

std::string SaveFile::GetFullPath() const {
    return GetDirectory() + GetFileName() + GetExtension();
}

int SaveFile::GetBitAt(int pos, int addr) {
    return (GetByteAt(addr) >> pos) & 1;
}

int SaveFile::GetByteAt(int addr) {
    OpenFile();
    this->file->seekg(addr);
    int byte = this->file->get();
    this->file->close();

    return byte;
}

const std::string& SaveFile::GetFileName() const {
    return this->fileName;
}

const std::string& SaveFile::GetExtension() const {
    return this->extension;
}

// byte range [0, 255]
void SaveFile::SetByteAt(int byte, int addr) {
    OpenFile();
    this->file->seekp(addr);
    this->file->put(byte);
    this->file->close();
}

void SaveFile::ORByteAt(int byte, int addr) {
    OpenFile();

    if (addr >= std::filesystem::file_size(GetFullPath())) {
        std::filesystem::resize_file(GetFullPath(), (size_t) addr + 1);
    }

    this->file->seekg(addr);
    byte |= this->file->get();
    this->file->seekp(addr);
    this->file->put(byte);
    this->file->close();
}

void SaveFile::ANDByteAt(int byte, int addr) {
    OpenFile();

    if (addr >= std::filesystem::file_size(GetFullPath())) {
        std::filesystem::resize_file(GetFullPath(), (size_t) addr + 1);
    }

    this->file->seekg(addr);
    byte &= this->file->get();
    this->file->seekp(addr);
    this->file->put(byte);
    this->file->close();
}

void SaveFile::SetBitAt(int bitpos, int addr) {
    ORByteAt((1 << bitpos), addr);
}

void SaveFile::UnsetBitAt(int bitpos, int addr) {
    ANDByteAt(~(1 << bitpos), addr);
}

void SaveFile::Reset() const {
    std::ofstream file(GetFullPath(), std::ios::binary | std::ios::trunc);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for reset: " << GetFullPath() << std::endl;
        return;
    }

    char zeros[MAX_ADDRESSES] = { 0 };
    file.write(zeros, MAX_ADDRESSES);
    file.close();
}


void SaveFile::SetDirectory(const std::string& directory) {
    this->directory = directory;
}

void SaveFile::SetFileName(const std::string& fileName) {
    this->fileName = fileName;
}

void SaveFile::SetExtension(const std::string& extension) {
    this->extension = extension;
}

void SaveFile::OpenFile() {
    if (file->is_open()) {
        return;
    }

    if (std::filesystem::exists(GetFullPath())) {
        file->open(GetFullPath(), std::ios::in | std::ios::out | std::ios::binary);
    } else {
        std::filesystem::create_directories(directory);
        file->open(GetFullPath(), std::ios::out | std::ios::binary);
        file->close();  // Close the file to reopen it in read/write mode
        file->open(GetFullPath(), std::ios::in | std::ios::out | std::ios::binary);
    }
}

std::ostream& operator<<(std::ostream& os, const SaveFile& sf) {
    os << sf.GetFullPath();
    return os;
}

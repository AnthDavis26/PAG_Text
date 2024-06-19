#pragma once
#include <iostream>
#include <fstream>
#include <memory>
#include <string>

class SaveFile {
public:
    SaveFile();
    SaveFile(const SaveFile& other);
    SaveFile(const std::string& directory, const std::string& fileName, const std::string& extension);
    SaveFile& operator=(const SaveFile& other);
    bool operator<(const SaveFile& other) const;
    bool operator==(const SaveFile& other) const;

    void OpenFile();
    void SetByteAt(int byte, int addr);
    void ORByteAt(int byte, int addr);
    void ANDByteAt(int byte, int addr);
    void SetBitAt(int pos, int addr);
    void UnsetBitAt(int bitpos, int addr);

    // Accessors
    const std::string& GetDirectory() const;
    const std::string& GetFileName() const;
    const std::string& GetExtension() const;
    std::string GetFullPath() const;
    int GetBitAt(int pos, int addr);
    int GetByteAt(int addr);

    // Mutators
    void Reset() const;
    void SetDirectory(const std::string& directory);
    void SetFileName(const std::string& fileName);
    void SetExtension(const std::string& extension);

private:
    std::string directory;
    std::string fileName;
    std::string extension;
    std::unique_ptr<std::fstream> file;
    static const int MAX_ADDRESSES = 1000;
};
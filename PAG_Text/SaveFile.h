#pragma once
#include <iostream>
#include <fstream>

class SaveFile
{
public:
	SaveFile();
	SaveFile(const SaveFile&);
	SaveFile(std::string directory);
	SaveFile(std::string directory, std::string fileName);
	SaveFile& operator=(const SaveFile&);

	void OpenFile();
	void SetByteAt(int byte, int addr);
	void ORByteAt(int byte, int addr);
	void ANDByteAt(int byte, int addr);
	void SetBitAt(int pos, int addr);
	void UnsetBitAt(int bitpos, int addr);

	// Accessors
	std::string GetFileName() const;
	std::string GetDirectory() const;
	std::string GetFullPath() const;
	int GetBitAt(int pos, int addr);
	int GetByteAt(int addr);
	std::fstream& GetFile();

	// Mutators
	void Reset();
	void SetDirectory(std::string directory);
	void SetFileName(std::string fileName);
private:
	std::string directory;
	std::string fileName;
	std::fstream file;
};
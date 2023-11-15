#pragma once
#include <iostream>
#include <fstream>

class SaveFile
{
public:
	SaveFile(std::string directory);
	SaveFile(std::string directory, std::string fileName);

	// Accessors
	std::string GetFileName();
	std::string GetDirectory();
	std::string GetFullPath();
	bool IsDefaultSave(); // TODO: reconsider this even existing

	// Mutators
	void SetByteAt(int byte, int addr);
	void ORByteAt(int byte, int addr);
	void ANDByteAt(int byte, int addr);
	void SetBitAt(int pos, int addr);
	void UnsetBitAt(int pos, int addr);
	void Reset();
	void SetAsDefaultSave(); // TODO: reconsider this even existing

	// Operator Overloads
	friend std::ostream& operator<<(std::ostream& os, const SaveFile& sf);
private:
	void OpenFile();
	
	std::string directory;
	std::string fileName;
	std::string fullPath;
	std::fstream file;
	bool isDefaultSave;
};


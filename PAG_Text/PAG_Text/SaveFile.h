#pragma once
#include <iostream>
#include <fstream>

class SaveFile
{
public:
	SaveFile(std::string directory, std::string filename);

	// Accessors
	std::string GetFullPath();
	std::string GetDirectory();

	// Mutators

	// Operator Overloads
	friend std::ostream& operator<<(std::ostream& os, const SaveFile& sf);

	// Byte Operations
	void SetByteAt(int byte, int addr);
	void ORByteAt(int byte, int addr);
	void ANDByteAt(int byte, int addr);
	void SetBitAt(int pos, int addr);
	void UnsetBitAt(int pos, int addr);
	void Reset();

private:
	void OpenFile();
	
	std::string directory;
	std::string filename;
	std::string fullpath;
	std::fstream file;
};


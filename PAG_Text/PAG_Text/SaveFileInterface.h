#pragma once
#include <iostream>

class SaveFileInterface
{
public:
	void SetByteAt(std::string path, std::string filename, int byte, int addr);
	void OrByteAt(std::string path, std::string filename, int byte, int addr);
	void ANDByteAt(std::string path, std::string filename, int byte, int addr);

private:
	void Helper_CheckFile(std::string fullpath, std::fstream &file);
	void Helper_PlaceByte(std::fstream& file, int byte, int addr);
};


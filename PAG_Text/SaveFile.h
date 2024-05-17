#pragma once
#include <iostream>
#include <fstream>

class SaveFile {
	public:
		SaveFile(const SaveFile&);
		SaveFile(std::string directory, std::string fileName, std::string extension);
		SaveFile& operator=(const SaveFile&);

		void OpenFile();
		void SetByteAt(int byte, int addr);
		void ORByteAt(int byte, int addr);
		void ANDByteAt(int byte, int addr);
		void SetBitAt(int pos, int addr);
		void UnsetBitAt(int bitpos, int addr);

		bool contentsEqualTo(SaveFile);

		// Accessors
		std::string GetDirectory() const;
		std::string GetFileName() const;
		std::string GetExtension() const;
		std::string GetFullPath() const;
		int GetBitAt(int pos, int addr);
		int GetByteAt(int addr);
		std::fstream& GetFile();

		// Mutators
		void Reset() const;
		void SetDirectory(std::string directory);
		void SetFileName(std::string fileName);
		void SetExtension(std::string extension);
	private:
		std::string directory;
		std::string fileName;
		std::string extension;
		std::fstream file;
		static const int MAX_ADDRESSES = 1000;
};
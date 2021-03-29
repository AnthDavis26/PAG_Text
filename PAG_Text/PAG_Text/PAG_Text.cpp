#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "SaveFile.h"

// Global Constants
const int I_MAX_SAVES = INT_MAX; 
const int I_MAX_SAVE_NAME_LENGTH = 30;
const std::string S_SAVE_DIRECTORY = ".\\Saves\\";
const std::string S_DEFAULT_SAVE_NAME = "SAVEFILE";
const std::string S_SAVE_EXTENSION = ".sav";

// Global Variables
int saveFileNumber = 0;

// Global Objects
std::vector<SaveFile> saveFiles;
//SaveFile testsave(S_SAVE_DIRECTORY, S_SAVE_NAME);

// Prototypes
void InitializeSaveFiles();
void PrintSaveFiles();
void PromptCreateSaveFile();
void CreateSaveFile(std::string fileName);

// Flow
int main()
{
	InitializeSaveFiles();
	std::cout << "Main screen" << std::endl;
	PrintSaveFiles();
	PromptCreateSaveFile();
}

void PrintSaveFiles()
{
	if (saveFiles.size() <= 0)
		std::cout << "No save files found." << std::endl;
	else
	{
		for (const auto& x : saveFiles)
			std::cout << x << std::endl;
	}
}

// TODO: Prompt overwrite option if file name exists
void PromptCreateSaveFile()
{
	std::string fileName = "";

	std::cout << "Save Name: ";
	std::getline(std::cin, fileName);

	fileName = fileName.substr(0, I_MAX_SAVE_NAME_LENGTH);

	std::cout << fileName;

	if (fileName == "")
		fileName = S_DEFAULT_SAVE_NAME + std::to_string(saveFileNumber);

	CreateSaveFile(fileName);
}

void CreateSaveFile(std::string fileName)
{
	saveFiles.push_back(SaveFile(S_SAVE_DIRECTORY, fileName+S_SAVE_EXTENSION));
}

void InitializeSaveFiles()
{
	// Search for and add list of files
	for (const auto& entry : std::filesystem::directory_iterator(S_SAVE_DIRECTORY))
	{
		std::string fileName = std::filesystem::path(entry).filename().string();

		if (fileName.starts_with(S_DEFAULT_SAVE_NAME) && fileName.ends_with(S_SAVE_EXTENSION))
			saveFileNumber++;

		if (fileName.ends_with(S_SAVE_EXTENSION))
			saveFiles.push_back(SaveFile(S_SAVE_DIRECTORY, fileName));
	}
}
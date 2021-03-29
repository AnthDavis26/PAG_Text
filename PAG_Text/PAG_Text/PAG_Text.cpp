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
int savefilenumber = 0;

// Global Objects
std::vector<SaveFile> savefiles;
//SaveFile testsave(S_SAVE_DIRECTORY, S_SAVE_NAME);

// Prototypes
void InitializeSaveFiles();
void PrintSaveFiles();
void PromptCreateSaveFile();
void CreateSaveFile(std::string filename);

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
	if (savefiles.size() <= 0)
		std::cout << "No save files found." << std::endl;
	else
	{
		for (const auto& x : savefiles)
			std::cout << x << std::endl;
	}
}

// TODO: Prompt overwrite option if file name exists
void PromptCreateSaveFile()
{
	std::string filename = "";

	std::cout << "Save Name: ";
	std::getline(std::cin, filename);

	filename = filename.substr(0, I_MAX_SAVE_NAME_LENGTH);

	std::cout << filename;

	if (filename == "")
		filename = S_DEFAULT_SAVE_NAME + std::to_string(savefilenumber);

	CreateSaveFile(filename);
}

void CreateSaveFile(std::string filename)
{
	savefiles.push_back(SaveFile(S_SAVE_DIRECTORY, filename+S_SAVE_EXTENSION));
}

void InitializeSaveFiles()
{
	// Search for and add list of files
	for (const auto& entry : std::filesystem::directory_iterator(S_SAVE_DIRECTORY))
	{
		std::string filename = std::filesystem::path(entry).filename().string();

		if (filename.starts_with(S_DEFAULT_SAVE_NAME) && filename.ends_with(S_SAVE_EXTENSION))
			savefilenumber++;

		if (filename.ends_with(S_SAVE_EXTENSION))
			savefiles.push_back(SaveFile(S_SAVE_DIRECTORY, filename));
	}
}
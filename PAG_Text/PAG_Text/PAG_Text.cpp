#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "SaveFile.h"
#include <regex>

// Global Constants
const int SAVES_MAX = INT_MAX; 
const int SAVE_NAME_LENGTH = 30;
const std::string SAVE_DIRECTORY = ".\\Saves\\";
const std::string SAVE_NAME_DEFAULT = "SAVEFILE_";
const std::string SAVE_EXTENSION = ".sav";

// Global Variables

// Global Objects
std::vector<SaveFile> saveFiles;
SaveFile currentSave(SAVE_DIRECTORY);

// Prototypes
void InitializeSaveFiles();
void PrintSaveFiles();
void PromptCreateSaveFile();
void CreateSaveFile(std::string fileName);
void CreateDefaultFile();
std::string ToLowercase(std::string str);
std::string ToUppercase(std::string str);
int ExtractDigits(std::string str);

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
		for (int i = 0; i < saveFiles.size(); i++)
			std::cout << i+1 << ". " << saveFiles[i].GetFileName() << std::endl;
	}
}

void PromptCreateSaveFile()
{
	// Prompt for input
	std::string fileName = "";
	std::cout << "Save Name: ";
	std::getline(std::cin, fileName);
	fileName = fileName.substr(0, SAVE_NAME_LENGTH);

	// TODO: Prompt overwrite option if file name exists, case-insensitive

	if (fileName == "")
		CreateDefaultFile();
	else
		CreateSaveFile(fileName);
}

void CreateSaveFile(std::string fileName)
{
	saveFiles.push_back(SaveFile(SAVE_DIRECTORY, fileName+SAVE_EXTENSION));
}

void CreateDefaultFile()
{
	std::regex pattern("(" + SAVE_NAME_DEFAULT + ")([0-9])*(" + SAVE_EXTENSION + ")");
	int maxNumber = 0;
	int num = 0;

	// Look for files with default naming pattern
	for (int i = 0; i < saveFiles.size(); i++)
	{
		if (std::regex_match(saveFiles[i].GetFileName(), pattern))
		{
			num = ExtractDigits(saveFiles[i].GetFileName());

			if (i > 0 && std::regex_match(saveFiles[i - 1].GetFileName(), pattern))
			{
				int num2 = ExtractDigits(saveFiles[i - 1].GetFileName());

				// Fill gaps between save files (e.g. create SAVEFILE_1
				// between SAVEFILE_0, SAVEFILE_4)
				if (num - num2 > 1)
				{
					maxNumber = num2 + 1;
					break;
				}
			}
			else if (i > 0 && num > 0)
				break;

			if (num > maxNumber)
				maxNumber = num;
			else if (num == maxNumber)
				maxNumber++;
		}
	}

	CreateSaveFile(SAVE_NAME_DEFAULT + std::to_string(maxNumber));
}

std::string ToLowercase(std::string str)
{
	std::string result = "";

	for (const char x : str)
		result += std::tolower(x);

	return result;
}

std::string ToUppercase(std::string str)
{
	std::string result = "";

	for (const char x : str)
		result += std::toupper(x);

	return result;
}

int ExtractDigits(std::string str)
{
	std::string result = "";

	for (const char x : str)
	{
		if (std::isdigit(x))
			result += x;
	}

	return std::stoi(result);
}

void InitializeSaveFiles()
{
	// Search for and add list of files
	for (const auto& entry : std::filesystem::directory_iterator(SAVE_DIRECTORY))
	{
		std::string fileName = std::filesystem::path(entry).filename().string();

		if (fileName.ends_with(SAVE_EXTENSION))
			saveFiles.push_back(SaveFile(SAVE_DIRECTORY, fileName));
	}
}
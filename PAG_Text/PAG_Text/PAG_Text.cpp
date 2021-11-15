#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "SaveFile.h"
#include <regex>
#include <conio.h> // Windows only

// Global Constants
const int SAVES_MAX = INT_MAX; 
const int SAVE_NAME_LENGTH = 30;
const std::string SAVE_DIRECTORY = "./Saves/";
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
void PromptDeleteSaveFile();
void DeleteSaveFile(char choice);
std::string ToLowercase(std::string str);
std::string ToUppercase(std::string str);
int ExtractDigits(std::string str);

// Flow
int main()
{
	char choice = -1;

	InitializeSaveFiles();

	std::cout << "POST-APOCALYPSE GEORGE" << std::endl;
	std::cout << "Copyright Anthony Davis\n\n" << std::endl;
	std::cout << "1. Resume Game" << std::endl;
	std::cout << "2. Create Save File" << std::endl;
	std::cout << "3. Load Save File" << std::endl;
	std::cout << "4. Delete Save File" << std::endl;
	std::cout << "5. Exit\n" << std::endl;

	while (choice < '2' ||  choice > '5')
		choice = _getch();

	if (choice == '2')
		PromptCreateSaveFile();
	else if (choice == '3')
		PrintSaveFiles(); // TODO: replace with PromptLoadSaveFile()
	else if (choice == '4')
		PromptDeleteSaveFile();
	else if (choice == '5')
		return 0;
}

void PrintSaveFiles()
{
	std::cout << "SAVE FILES" << std::endl;

	// TODO: implement page turning with arrow keys
	if (saveFiles.size() <= 0)
		std::cout << "No save files found." << std::endl;
	else
	{
		for (int i = 0; i < saveFiles.size(); i++)
			std::cout << i+1 << ". " << saveFiles[i].GetFileName() << std::endl;
	}
}


void PromptDeleteSaveFile()
{
	char choice = -1;

	PrintSaveFiles();
	std::cout << "\nFile Number: ";

	while (choice <= '0' || choice > saveFiles.size()+'0')
		choice = _getch();

	DeleteSaveFile(choice);
}

void DeleteSaveFile(char choice)
{
	choice -= '0';
	choice--;

	if (choice < saveFiles.size())
	{
		std::filesystem::remove(saveFiles[choice].GetFullPath());
		saveFiles.erase(saveFiles.begin() + choice);
	}
	else
		std::cout << "File not found." << std::endl;
}

void PromptCreateSaveFile()
{
	// Prompt for input
	std::string fileName = "";
	std::cout << "Create Save File" << std::endl;
	std::cout << "Save Name: ";
	std::getline(std::cin, fileName);
	fileName = fileName.substr(0, SAVE_NAME_LENGTH);

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
		// Fill gaps between save files (e.g. create SAVEFILE_1
		// between SAVEFILE_0, SAVEFILE_4)
		if (std::regex_match(saveFiles[i].GetFileName(), pattern))
		{
			num = ExtractDigits(saveFiles[i].GetFileName());

			if (i > 0 && std::regex_match(saveFiles[i - 1].GetFileName(), pattern))
			{
				int num2 = ExtractDigits(saveFiles[i - 1].GetFileName());

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

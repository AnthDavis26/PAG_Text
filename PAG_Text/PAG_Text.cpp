#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include "SaveFile.h"
#include <regex>
#include <conio.h> // Windows only
#include "Utils.h"

// Global Constants
const std::string STRING_SAVE_DIRECTORY = "./Saves/";
const std::string STRING_SAVE_NAME_DEFAULT = "SAVEFILE_";
const std::string STRING_SAVE_EXTENSION = ".sav";
const std::string STRING_GAME_TITLE = "Post-Apocalypse George";
const std::string STRING_COPYRIGHT = "Copyright Anthony Davis";
const int CHOICE_RESUME_GAME = 1;
const int CHOICE_NEW_GAME = 2;
const int CHOICE_LOAD_SAVE = 3;
const int CHOICE_DELETE_SAVE = 4;
const int CHOICE_EXIT_GAME = 5;
const int SAVES_MAX = 100;
const int SAVE_NAME_LENGTH = 30;
const int MIN_FILE_CHOICE = 0;
const std::vector<int> VALID_MAIN_MENU_CHOICES = { CHOICE_RESUME_GAME,
	CHOICE_NEW_GAME, CHOICE_LOAD_SAVE, CHOICE_DELETE_SAVE, CHOICE_EXIT_GAME };

// Global Variables

// Global Objects
std::vector<SaveFile> saveFiles;
SaveFile currentSave(STRING_SAVE_DIRECTORY);

// Prototypes
void RunMainMenu();
void ResumeGame();
void RunExitGame();
void InitializeSaveFiles();
void PrintSaveFiles();
void PromptCreateSaveFile();
void CreateSaveFile(std::string fileName);
void CreateDefaultFile();
void PromptDeleteSaveFile();
void DeleteSaveFileNumber(int choice);
bool IsValidMainMenuChoice(int choice);
bool IsValidFileChoice(int choice);
int CharNumToInt(char ch);
int EnterChoice();

int CharNumToInt(char ch) {
	return ch - '0';
}

void RunMainMenu() {
	InitializeSaveFiles();
	std::cout << STRING_GAME_TITLE << std::endl;
	std::cout << STRING_COPYRIGHT << std::endl;
	std::cout << "\n\n" << std::endl;
	std::cout << CHOICE_RESUME_GAME << ". Resume Game" << std::endl;
	std::cout << CHOICE_NEW_GAME << ". New Game" << std::endl;
	std::cout << CHOICE_LOAD_SAVE << ". Load Save File" << std::endl;
	std::cout << CHOICE_DELETE_SAVE << ". Delete Save File" << std::endl;
	std::cout << CHOICE_EXIT_GAME << ". Exit" << std::endl;

	int choice = -1;

	while (!IsValidMainMenuChoice(choice)) {
		choice = EnterChoice();
	}

	switch (choice) {
		case CHOICE_RESUME_GAME:
			// ResumeGame();
			break;
		case CHOICE_NEW_GAME:
			PromptCreateSaveFile();
			break;
		case CHOICE_LOAD_SAVE:
			PrintSaveFiles();
			break;
		case CHOICE_DELETE_SAVE:
			PromptDeleteSaveFile();
			break;
		case CHOICE_EXIT_GAME:
			RunExitGame();
			break;
		default:
			std::cout << "INVALID MAIN MENU SELECTION. This should not happen. Please report"
				<< " to the dev at anthony.m.davis.26@gmail.com." << std::endl;
	}
}

void ResumeGame() {
}

void RunExitGame() {
	exit(0);
}

void PrintSaveFiles()
{
	std::cout << "SAVE FILES" << std::endl;
	if (saveFiles.empty()) {
		std::cout << "No save files found." << std::endl;
	}
	else {
		for (int i = 0; i < saveFiles.size(); i++) {
			std::cout << i + 1 << ". " << saveFiles[i].GetFileName() << std::endl;
		}
	}
}

int EnterChoice() {
	return CharNumToInt(_getch());
}

void PromptDeleteSaveFile()
{
	int choice = -1;
	PrintSaveFiles();
	std::cout << "\nFile Number: ";
	while (!IsValidFileChoice(choice)) {
		choice = EnterChoice();
	}
	DeleteSaveFileNumber(choice);
}

bool IsValidFileChoice(int choice) {
	return (choice >= MIN_FILE_CHOICE && choice <= saveFiles.size());
}

void DeleteSaveFileNumber(int choice)
{
	if (choice <= saveFiles.size()) {
		choice -= 1;
		std::filesystem::remove(saveFiles[choice].GetFullPath());
		saveFiles.erase(saveFiles.begin() + choice);
	}
	else {
		std::cout << "File not found." << std::endl;
	}
}

void PromptCreateSaveFile()
{
	// Prompt for input
	std::string fileName = "";
	std::cout << "Create Save File" << std::endl;
	std::cout << "Save Name: ";
	std::getline(std::cin, fileName);
	fileName = fileName.substr(0, SAVE_NAME_LENGTH);

	if (fileName == "") {
		CreateDefaultFile();
	}
	else {
		CreateSaveFile(fileName);
	}
}

void CreateSaveFile(std::string fileName)
{
	saveFiles.push_back(SaveFile(STRING_SAVE_DIRECTORY, fileName+STRING_SAVE_EXTENSION));
}

void CreateDefaultFile()
{
	// TODO: make pattern a global constant to avoid reinitialization
	std::regex pattern("(" + STRING_SAVE_NAME_DEFAULT + ")([0-9])*(" + STRING_SAVE_EXTENSION + ")");
	int maxNumber = 0;
	int num = 0;

	// Look for files with default naming pattern
	for (int i = 0; i < saveFiles.size(); i++) {
		// Fill gaps between save files (e.g. create SAVEFILE_1
		// between SAVEFILE_0, SAVEFILE_4)
		if (std::regex_match(saveFiles[i].GetFileName(), pattern)) {
			num = Utils::ExtractDigitsFromString(saveFiles[i].GetFileName());

			if (i > 0 && std::regex_match(saveFiles[i - 1].GetFileName(), pattern)) {
				int num2 = Utils::ExtractDigitsFromString(saveFiles[i - 1].GetFileName());
				if (num - num2 > 1) {
					maxNumber = num2 + 1;
					break;
				}
			}
			else if (i > 0 && num > 0) {
				break;
			}

			if (num > maxNumber) {
				maxNumber = num;
			}
			else if (num == maxNumber) {
				maxNumber++;
			}
		}
	}

	CreateSaveFile(STRING_SAVE_NAME_DEFAULT + std::to_string(maxNumber));
}

bool IsValidMainMenuChoice(int choice) {
	for (int i : VALID_MAIN_MENU_CHOICES) {
		if (choice == i) {
			return true;
		}
	}
	return false;
}

void InitializeSaveFiles()
{
	// Search for and add list of files
	for (const auto& entry : std::filesystem::directory_iterator(STRING_SAVE_DIRECTORY)) {
		std::string fileName = std::filesystem::path(entry).filename().string();
		if (fileName.ends_with(STRING_SAVE_EXTENSION)) {
			saveFiles.push_back(SaveFile(STRING_SAVE_DIRECTORY, fileName));
		}
	}
}

// Flow
int main()
{
	RunMainMenu();
	return 0;
}

// TODO: implement load save to set current save file attributes to those of the loaded save file
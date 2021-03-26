#include <iostream>
#include <filesystem>
#include <fstream>
#include "SaveFile.h"

// Global Constants
const std::string S_SAVE_PATH = ".\\Saves\\";
const std::string S_SAVE_FILE = "SAV";

// Global Objects
SaveFile testsave(S_SAVE_PATH, S_SAVE_FILE);

// Prototypes

// Flow
int main()
{
	testsave.SetByteAt(0x1F, 0x123);
}
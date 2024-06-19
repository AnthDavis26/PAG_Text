#pragma once
#include "Rules.h"
#include <string>
#include "InputKeys.h"

namespace Strings {
	static const std::string TITLE = "Post-Apocalyptic George";
	static const std::string COPYRIGHT = "Copyright Anthony Davis";
	static const std::string DEV_EMAIL = "anthony.m.davis.26@gmail.com";

	static const std::string PROMPT_TOO_LONG = "(Your prompt was too long. Please enter something up to "
		+ std::to_string(Rules::MAX_PROMPT_LENGTH) + " characters long.)";
	static const std::string PLEASE_REPORT_ERROR = "Please report this error to " + Strings::DEV_EMAIL + ".";
	static const std::string INVALID_FILE_SELECT = "Invalid file select screen choice. "
		+ Strings::PLEASE_REPORT_ERROR;
	static const std::string PRESS_FOR_YES_OR_NO = std::string{ InputKeys::MENU_CHOICE_YES } + ". Yes\t" +
		std::string{ InputKeys::MENU_CHOICE_NO } + ". No";
	static const std::string PRESS_ANY_KEY = "Press any key to continue.";
	static const std::string ENTER_TEXT_COMMAND = "Enter your text command (press ENTER when you're done):";
	static const std::string PRESS_TO_PAUSE = "Press " + std::string{ InputKeys::PAUSE } + " to pause.";

	static const std::string WARNING_OVERWRITE_WITH_NEW_GAME =
		"Restart progress?\n\n"
		"WARNING: You'll LOSE all progress you've made!\n"
		"If you want to back up your save, resume game and then choose 'SAVE GAME'.\n\n"
		"THIS CANNOT BE UNDONE! Are you ABSOLUTELY sure you want to restart?";

	static const std::string WARNING_OVERWRITE_WITH_LOAD_GAME = 
		"WARNING: You will lose ALL progress you have made so far!\n"
		"If you want to back up your save, resume game and then choose 'SAVE GAME'.\n\n"
		"THIS CANNOT BE UNDONE! Are you ABSOLUTELY sure you want to load this file?";

	static const std::string INVALID_MAIN_MENU_SELECTION = 
		"INVALID MAIN MENU SELECTION. This should not happen. Please report"
		" this error to the dev at " + Strings::DEV_EMAIL + ".";

	static const std::string ALREADY_ATE_TRASH = "(You already ate the trash, you disgusting animal.)";
	static const std::string ATE_TRASH = "(You ate the trash. Now your breath is rancid. You happy?)";
	static const std::string SAVE_DEFAULT_DIRECTORY = "./Saves/";
	static const std::string SAVE_DEFAULT_EXTENSION = ".sav";
	static const std::string SAVE_CURRENT_NAME = "~CURRENT";
}
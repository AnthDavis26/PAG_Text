#pragma once
#include "Rules.h"
#include <string>

namespace Strings {
	static const std::string PROMPT_TOO_LONG = "Your prompt was too long. Please enter something up to "
		+ std::to_string(Rules::MAX_PROMPT_LENGTH) + " characters long.";

	static const std::string ALREADY_ATE_TRASH = "You already ate the trash, you disgusting animal.";
	static const std::string ATE_TRASH = "You ate the trash. Now your breath is rancid. You happy?";
}
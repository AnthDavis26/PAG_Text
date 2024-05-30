#include "Prompt.h"
#include <conio.h>
#include "InputKeys.h"
#include <iostream>
#include "Utils.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Rules.h"
#include <unordered_set>
#include "Thesaurus.h"
#include <ctime>
#include "Strings.h"

char Prompt::choice = -1;
std::string Prompt::enteredPrompt = "";
bool Prompt::promptWasTooLong = false;

void Prompt::PromptChoiceUntil(std::function<bool()> conditionFunction) {
	Prompt::ResetChoice();

	do {
		Prompt::SetChoice(_getch());
	} while (!conditionFunction());
	
}

void Prompt::PromptYesOrNo() {
	std::cout << InputKeys::MENU_CHOICE_YES << ". Yes\t" << InputKeys::MENU_CHOICE_NO << ". No" << std::endl;
	Prompt::PromptChoiceUntil([]() {
		return Prompt::PickedYes() || Prompt::PickedNo();
	});
}

void Prompt::PromptPressKey() {
	std::cout << "Press any key to continue." << std::endl;
	_getch();
}

void Prompt::CustomPrompt() {
	std::cout << "Enter your prompt (press ENTER when you're done):" << std::endl;
	std::getline(std::cin, Prompt::GetCustomPrompt());
	Utils::Trim(Prompt::GetCustomPrompt());

	if (Prompt::GetCustomPrompt().size() > Rules::MAX_PROMPT_LENGTH) {
		std::cout << Strings::PROMPT_TOO_LONG << std::endl;
		Prompt::PromptPressKey();
		Utils::ClearScreen();
		Prompt::CustomPrompt();
		return;
	}

	Utils::ClearScreen();
	Prompt::ProcessCustomPrompt();
}

void Prompt::ProcessCustomPrompt() {
	if (Prompt::GetCustomPrompt().empty()) {
		std::cout << "Eh, never mind." << std::endl;
	} else if (Navigator::AtHouseKitchen()) {
		if (Prompt::GetCustomPrompt() == "take out trash" || Prompt::GetCustomPrompt() == "take out the trash") {
			if (SaveManager::AteTrash()) {
				std::cout << "But there's no trash to be taken out. Weird..." << std::endl;
			}
			else {
				std::cout << "Nah, I'm far too irresponsible to do that." << std::endl;
			}
		} else if (Prompt::PromptMatchesEatTrash(enteredPrompt)) {
			if (SaveManager::AteTrash()) {
				std::cout << Strings::ALREADY_ATE_TRASH << std::endl;
			}
			else {
				std::cout << Strings::ATE_TRASH << std::endl;
				SaveManager::SetAteHouseTrash();
			}
		} else {
			Prompt::InvalidCustomPromptResponse();
		}
	} else {
		Prompt::InvalidCustomPromptResponse();
	}

	std::cout << std::endl;
}

std::string& Prompt::GetCustomPrompt() {
	return enteredPrompt;
}

bool Prompt::PickedYes() {
	return Prompt::GetChoice() == InputKeys::MENU_CHOICE_YES;
}

bool Prompt::PickedNo() {
	return Prompt::GetChoice() == InputKeys::MENU_CHOICE_NO;
}

char& Prompt::GetChoice() {
	return choice;
}

bool Prompt::PromptMatchesEatTrash(std::string prompt) {
	bool containsEatSynonym = false, containsTrashSynonym = false;
	std::string substring = "";
	prompt += ' ';

	for (char& ch : prompt) {
		if (std::isspace(ch)) {
			if (!containsEatSynonym) {
				containsEatSynonym = Thesaurus::IsEatSynonym(substring);
			}

			if (!containsTrashSynonym) {
				containsTrashSynonym = Thesaurus::IsTrashSynonym(substring);
			}

			if (containsEatSynonym && containsTrashSynonym) {
				return true;
			}
			
			substring.clear();
		} else {
			substring += ch;
		}
	}

	return containsEatSynonym && containsTrashSynonym;
}

void Prompt::ResetChoice() {
	choice = -1;
}

void Prompt::SetChoice(char ch) {
	choice = ch;
}

void Prompt::InvalidCustomPromptResponse() {
	std::vector<std::string> responses = {
		"I don't know why I said that. Anyway...",
		"Wait, what was I doing again? Oh yeah...",
		"I keep thinking about that. Why?",
		"I think that's how the song goes.",
		"Huh, what? Anyway...",
		"I don't understand what that means.",
		"I don't remember what I was doing.",
		"Ha, as if.",
		"...Is what I would never say.",
		"Nah, just kidding.",
		"That's something I should keep to myself.",
		"Imagine actually saying that.",
		"Moving on...",
		"That's a weird thing for me to say.",
		"Why did I say that?",
		"I already forgot what I said.",
		"Can't say that.",
		"Shouldn't say that.",
		"I sure love speaking gibberish.",
		"Maybe later.",
		"Not right now. Or possibly ever.",
		"Maybe that's not a good idea.",
		"I don't know what that means.",
		"I'll never forget when they told me that.",
		"I never understood that quote.",
		"I really need to focus.",
		"Profound wisdom to live by.",
		"I feel like someone else made me say that.",
		"I don't know how to react.",
		"Yeah.",
		"Nah.",
		"Maybe.",
		"Ha, so true.",
		"[insert invalid prompt response here]",
		"Wait, who am I talking to?",
		"Who said that?",
		"Yes, quite.",
		"Not likely.",
		"Indeed.",
		"How would that work?",
		//"TRAINED HIS DREAM"
		"Sometimes."
	};
	std::cout << responses[Utils::RandomNumber(0, (int) responses.size())] << std::endl;
}

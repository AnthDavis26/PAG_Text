#include "InputChecker.h"
#include "Prompter.h"
#include "SaveManager.h"
#include "Strings.h"
#include "Thesaurus.h"

bool InputChecker::ChoiceMatchesCommands(const std::unordered_map<char, std::function<void()>>& validCommands) {
	return validCommands.find(Prompter::GetChoice()) != validCommands.end();
}

bool InputChecker::IsDefaultCommand() {
	return Prompter::GetChoice() == InputKeys::PAUSE
		|| Prompter::GetChoice() == InputKeys::TEXT_ENTRY;
}

bool InputChecker::PickedYes() {
	return Prompter::GetChoice() == InputKeys::MENU_CHOICE_YES;
}

bool InputChecker::PickedNo() {
	return Prompter::GetChoice() == InputKeys::MENU_CHOICE_NO;
}

bool InputChecker::IsCommandEatTrash() {
	Prompter::SetTextEntry(Prompter::GetTextCommand() + ' ');
	bool containsEatSynonym = false, containsTrashSynonym = false;
	std::string substring = "";

	for (const char ch : Prompter::GetTextCommand()) {
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
		}
		else {
			substring += ch;
		}
	}

	return containsEatSynonym && containsTrashSynonym;
}

void InputChecker::ProcessCustomCommand() {
	if (Prompter::GetTextCommand().empty()) {
		Prompter::Print("Eh, never mind.");
	}
	else if (Navigator::AtHouseKitchen()) {
		if (Prompter::GetTextCommand() == "take out trash"
			|| Prompter::GetTextCommand() == "take out the trash") {
			if (SaveManager::AteHouseKitchenTrash()) {
				Prompter::Print("But there's no trash to be taken out. Weird...");
			}
			else {
				Prompter::Print("Nah, I'm too irresponsible to do that.");
			}
		}
		else if (InputChecker::IsCommandEatTrash()) {
			if (SaveManager::AteHouseKitchenTrash()) {
				Prompter::Print(Strings::ALREADY_ATE_TRASH);
			}
			else {
				Prompter::Print(Strings::ATE_TRASH);
				SaveManager::SetAteHouseKitchenTrash();
			}
		}
		else {
			Prompter::ShowInvalidTextResponse();
			Prompter::Print("");
		}
	}
	else if (InputChecker::IsCommandEatTrash()) {
		Prompter::Print("There is no sweet, delicious trash for me to eat around here.");
	}
	else {
		Prompter::ShowInvalidTextResponse();
		Prompter::Print("");
	}

	Prompter::Print("");
}
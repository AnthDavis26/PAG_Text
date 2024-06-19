#include "Prompter.h"
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
#include "InputChecker.h"

char Prompter::choice = -1;
std::string Prompter::customCommand = "";
bool Prompter::promptWasTooLong = false;
const std::vector<std::string> Prompter::invalidTextResponses = {
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
	"Sometimes."
};

void Prompter::PromptChoiceUntil(std::function<bool()> conditionFunction) {
	Prompter::ResetChoice();

	do {
		Prompter::PromptChoice();
	} while (!conditionFunction());
	
}

void Prompter::PromptUntilYesOrNo() {
	Prompter::Print(Strings::PRESS_FOR_YES_OR_NO);

	Prompter::PromptChoiceUntil([]() {
		return InputChecker::PickedYes() || InputChecker::PickedNo();
	});

	Prompter::ClearScreen();
}

void Prompter::PromptPressKey() {
	Prompter::Print(Strings::PRESS_ANY_KEY);
	#pragma warning(push)
	#pragma warning(disable : 6031)
	Prompter::PromptChoice();
	#pragma warning(pop)
}

void Prompter::PromptTextCommand() {
	Prompter::Print(Strings::ENTER_TEXT_COMMAND);
	std::string command = Prompter::InputText();
	Utils::Trim(command);
	Prompter::SetTextEntry(command);
	Prompter::ClearScreen();

	if (Prompter::GetTextCommand().size() > Rules::MAX_PROMPT_LENGTH) {
		Prompter::Print(Strings::PROMPT_TOO_LONG);
		Prompter::Print("");
		Navigator::GoToCurrentLocation();
		return;
	}

	InputChecker::ProcessCustomCommand();
	Navigator::GoToCurrentLocation();
}

void Prompter::ShowDefaultControls() {
	Prompter::Print("");
	Prompter::ShowPressToPause();
	Prompter::ShowPressToEnterText();
}

void Prompter::ShowInvalidChoice() {
	Prompter::Print("INVALID CHOICE (" + std::string{ Prompter::GetChoice() } + ")");
}

void Prompter::ShowGameInfo() {
	Prompter::Print(Strings::TITLE);
	Prompter::Print(Strings::COPYRIGHT);
}

void Prompter::ShowPressToPause() {
	Prompter::Print(Strings::PRESS_TO_PAUSE);
}

void Prompter::ShowPressToEnterText() {
	Prompter::Print("Press " + std::string(1, InputKeys::TEXT_ENTRY) + " to enter text.");
}

void Prompter::PromptChoice() {
	Prompter::SetChoice(_getch());
}

void Prompter::Print(const std::string& text) {
	std::cout << text << std::endl;
}

std::string Prompter::GetTextCommand() {
	return Prompter::customCommand;
}

void Prompter::ClearScreen() {
	system("cls"); // Windows console only
}

void Prompter::SceneTitle(std::string title) {
	Prompter::Print("- " + Utils::ToUppercase(title) + " -\n");
}

std::string Prompter::InputText() {
	std::string input;
	std::getline(std::cin, input);
	return input;
}

std::string& Prompter::GetTextCommandRef() {
	return Prompter::customCommand;
}

void Prompter::SetTextEntry(std::string prompt) {
	Prompter::customCommand = prompt;
}

char Prompter::GetChoice() {
	return Prompter::choice;
}

void Prompter::ResetChoice() {
	Prompter::choice = -1;
}

void Prompter::SetChoice(char ch) {
	Prompter::choice = ch;
}

void Prompter::ShowInvalidTextResponse() {
	int n = (int) Prompter::invalidTextResponses.size();
	int index = Utils::RandomNumber(0, n);
	Prompter::Print(Prompter::invalidTextResponses[index]);
}

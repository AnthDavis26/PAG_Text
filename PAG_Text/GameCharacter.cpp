#include "GameCharacter.h"
#include "Prompter.h"
#include "Utils.h"

GameCharacter::GameCharacter(std::string name) {
	this->SetName(name);
}

std::string GameCharacter::GetName() const {
	return this->displayName;
}

void GameCharacter::SetName(std::string name) {
	this->displayName = name;
}

void GameCharacter::Speak(std::string dialogue) const {
	Prompter::Print(Utils::ToUppercase(this->GetName()) + "\n\"" + dialogue + "\"\n");
}

#include "GameCharacter.h"
#include "Prompter.h"
#include "Utils.h"

GameCharacter::GameCharacter(std::string name, std::string gender, int yearsAge, int maxHealth) 
	: GameActor(name) {
	this->SetGender(gender);
	this->SetAge(yearsAge);
	this->SetHealth(maxHealth);
	this->SetMaxHealth(maxHealth);
}

std::string GameCharacter::GetGender() const {
	return this->gender;
}

void GameCharacter::Speak(std::string dialogue) const {
	Prompter::Print(Utils::ToUppercase(this->GetName()) + "\n\"" + dialogue + "\"\n");
}

void GameCharacter::SetGender(std::string gender) {
	this->gender = gender;
}
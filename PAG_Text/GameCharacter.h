#pragma once
#include <string>
#include "GameActor.h"

class GameCharacter : public GameActor {
	public:
		GameCharacter(std::string name, std::string gender, int yearsAge, int maxHealth);
		std::string GetGender() const;
		void SetGender(std::string);
		void Speak(std::string dialogue) const;

	private:
		std::string gender;
};


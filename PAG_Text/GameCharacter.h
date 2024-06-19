#pragma once
#include <string>

class GameCharacter {
	public:
		GameCharacter(std::string name);
		std::string GetName() const;
		void SetName(std::string name);
		void Speak(std::string dialogue) const;
	private:
		std::string displayName;
};


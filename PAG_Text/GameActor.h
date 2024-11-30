#pragma once
#include <string>

class GameActor {
	public:
		GameActor(std::string name);
		std::string GetName() const;
		bool IsDestroyed() const;
		int GetAge() const;
		int GetHealth() const;
		int GetMaxHealth() const;
		void HealActor(GameActor& actor, int health) const;
		void HitActor(GameActor& actor, int damage) const;
		void Destroy();
		void SetDestroyed(bool);
		void SetFullHealth();
		void AddHealth(int health);
		void AddHealthUncapped(int health);
		void ReduceHealth(int health);
		void ReduceHealthUncapped(int health);
		void SetName(std::string);
		void SetAge(int year);
		void SetHealth(int health);
		void SetMaxHealth(int health);

	private:
		std::string displayName;
		bool isDestroyed;
		int age;
		int health;
		int maxHealth;
};
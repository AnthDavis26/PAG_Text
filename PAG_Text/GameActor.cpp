#include "GameActor.h"
#include <string>

GameActor::GameActor(std::string name) {
	this->SetName(name);
}

std::string GameActor::GetName() const {
	return this->displayName;
}

void GameActor::HealActor(GameActor& actor, int health) const {
	actor.AddHealth(health);
}

void GameActor::HitActor(GameActor& actor, int damage) const {
	actor.ReduceHealth(damage);
}

void GameActor::Destroy() {
	this->SetDestroyed(true);
	this->SetHealth(0);
}

void GameActor::SetDestroyed(bool b) {
	this->isDestroyed = b;
}

void GameActor::SetFullHealth() {
	this->SetHealth(this->GetMaxHealth());
}

bool GameActor::IsDestroyed() const {
	return this->isDestroyed;
}

int GameActor::GetAge() const {
	return this->age;
}

int GameActor::GetHealth() const {
	return this->health;
}

int GameActor::GetMaxHealth() const {
	return this->maxHealth;
}

void GameActor::AddHealth(int health) {
	int newHealth = this->GetHealth() + health;

	if (newHealth > this->GetMaxHealth()) {
		this->SetHealth(this->GetMaxHealth());
	} else {
		this->SetHealth(newHealth);
	}
}

void GameActor::AddHealthUncapped(int health) {
	this->SetHealth(this->GetHealth() + health);
}

void GameActor::ReduceHealth(int health) {
	int newHealth = this->GetHealth() - health;

	if (newHealth < 0) {
		this->SetHealth(0);
	}
	else {
		this->SetHealth(newHealth);
	}
}

void GameActor::ReduceHealthUncapped(int health) {
	this->AddHealthUncapped(-health);
}

void GameActor::SetName(std::string name) {
	this->displayName = name;
}

void GameActor::SetAge(int year) {
	this->age = year;
}

void GameActor::SetHealth(int health) {
	this->health = health;
}

void GameActor::SetMaxHealth(int health) {
	this->maxHealth = health;
}

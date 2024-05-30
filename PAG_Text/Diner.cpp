#include "Diner.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Rules.h"

void Diner::Start() {
	if (Rules::SAVE_AT_DINER) {
		SaveManager::SetAtDiner();
	}
	std::cout << "In diner." << std::endl;
}

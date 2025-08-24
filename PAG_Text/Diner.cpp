#include "Diner.h"
#include "SaveManager.h"
#include "LocationKeys.h"
#include "Rules.h"
#include "Prompter.h"
#include "GameCharacters.h"

void Diner::Start() {
	Prompter::SceneTitle("Diner");
	Prompter::Print("You're inside the local diner. It has no name.\n");

	GameCharacter& GCGeorge = GameCharacters::GEORGE;
	GameCharacter& GCDinerOwner = GameCharacters::DINER_OWNER;

	if (SaveManager::KilledDinerOwnerThenLeft()) {
		SaveManager::SetKilledDinerOwnerThenLeft(false);
		GCDinerOwner.SetFullHealth();
		SaveManager::SetKilledDinerOwner(false);
		GCGeorge.Speak("Wait, didn't I kill you?");
		GCDinerOwner.Speak("Yes, but I'm better now!");
		GCGeorge.Speak("That's such a relief! I'm so glad you're ok!");
		GCDinerOwner.Speak("Thank you, so am I!");
	} else {
		GCGeorge.Speak("Too bad they don't have food here, just condiments.");
	}

	if (Rules::CAN_SAVE_AT_DINER) {
		SaveManager::SetCurrentLocation(LocationKeys::DINER);
	}

	Prompter::Print(
		"1. Leave the diner\n"
		"2. Punch the diner owner"
	);

	Prompter::ShowDefaultControls();

	Prompter::PromptUntilValidCommand(
		CMD('1', [] {
			if (SaveManager::KilledDinerOwner()) {
				SaveManager::SetKilledDinerOwnerThenLeft(true);
			}

			Navigator::GoToHomeStreet(); }),
		CMD('2', [] {
			Prompter::Print("You punched the diner owner.");
			Prompter::Print("");

			GameCharacter& GCGeorge = GameCharacters::GEORGE;
			GameCharacter& GCDinerOwner = GameCharacters::DINER_OWNER;

			if (!SaveManager::KilledDinerOwner()) {
				GCGeorge.HitActor(GCDinerOwner, 100);	
				
				if (GCDinerOwner.GetHealth() > 0) {
					GCDinerOwner.Speak("Ow, you hit me.");
					GCGeorge.Speak("Sorry.");
				} else {
					GCDinerOwner.Speak("Ow, you killed me.");
					SaveManager::SetKilledDinerOwner(true);
					GCGeorge.Speak("Good.");
				}
			} else {
				GCGeorge.Speak("Yep, still dead.");
			}

			Diner::Start(); 
		})
	);
}

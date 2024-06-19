#pragma once
#include "Location.h"

class House : public Location {
	public:
		static void Start();
		static void EnterKitchen();
		static void EnterBathroom();
		static void EnterBedroom();
		static void EnterLivingRoom();
};


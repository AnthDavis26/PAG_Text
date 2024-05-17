#include "Location.h"
#include <iostream>

Location::Location(std::string name) {
	this->name = name;
}

std::string Location::GetName() const {
	return name;
}

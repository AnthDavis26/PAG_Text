#include "Location.h"
#include <iostream>

Location::Location(std::string name) {
	this->name = name;
}

const std::string Location::GetName() const {
	return this->name;
}

#include "Location.h"
#include <iostream>

Location::Location(std::string name) {
	this->name = name;
}

std::string Location::GetName() const {
	return name;
}

std::unordered_map<int, int>& Location::GetProps() {
	return props;
}

void Location::AddProp(int propKey) {
	// TODO: implement AddProp
}

void Location::RemoveProp(int propKey) {
	// TODO: implement RemoveProp
}

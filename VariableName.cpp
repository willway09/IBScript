#include "VariableName.hpp"

int VariableName::hashCode() {
	int hash = 2166136261;

	for(std::string::iterator it = std::string::begin(); it != std::string::end(); ++it) {
		hash = hash ^ *it;
		hash = hash * 16777619;
	}

	return hash;
}

bool VariableName::equals(VariableName* vn) {
	if(std::string::compare(*vn) == 0) return true;
	else return false;
}
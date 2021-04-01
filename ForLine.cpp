#include "ForLine.hpp"
#include <cstdlib>
#include <regex>

ForLine::ForLine(std::string ln, VariableHashMap& vars, int s) : Line("", vars, s) {
	
	std::cmatch cm;
	try {
		std::regex_match(ln.c_str(), cm, forLineRegex);
	} catch (std::exception&) {
		throw RuntimeException("Invalid phrasing for for-style loop");
	}
	
	if(cm.size() != 4) {
		throw RuntimeException("Invalid phrasing for for-style loop");
	}

	
	
	loopVarName = new VariableName(cm[1]);
	
	initializationLine = new Line(*loopVarName + " = " + std::string(cm[2]), vars, scope);
	
	line = *loopVarName + " <= " + std::string(cm[3]);

}

Variable* ForLine::evaluate() {
	if(loopVar != nullptr)
		variables.add(new VariableName(*loopVarName), loopVar);

	return Line::evaluate();
}

void ForLine::print() {
	
}

void ForLine::step() {
	(Line(*loopVarName + " = " + *loopVarName + " + 1", variables, scope)).execute(); //Execute an expression to step the variable
	if(loopVar != nullptr) {
		loopVar = new Variable(variables.get(loopVarName));
		if(loopVar == nullptr) {
			throw RuntimeException("Invalid Variable");
		}
	}
}

void ForLine::initialize() {
	
		
	bool variableExists = true;
	
	if(!variables.containsKey(loopVarName)) {
		variables.add(new VariableName(*loopVarName), new Variable(new int(0),Types::INT,scope));
		variableExists = false;
	}
	initializationLine->execute(); //Run line to initialize the loop variable
	
	if(!variableExists)
		loopVar = new Variable(variables.get(loopVarName));
}

void ForLine::printSimple() {
	
}

ForLine::~ForLine() {
	delete loopVar;
	delete loopVarName;
	delete initializationLine;
}

void ForLine::execute() {
	throw RuntimeException("For Lines should not be executed");
}

const std::regex ForLine::forLineRegex = std::regex("([A-Z]+)\\s+from\\s+(.*?)\\s+to\\s+(.*)");
#include "Loop.hpp"
#include <cstdlib>

Loop::Loop(ListIterator<std::string>* tokensIt, std::string* lines, int lineCount, int& lineNumber, VariableHashMap& vars, int s) : ControlStructure(vars, s, Statement::LOOP) {
	
	tokensIt->next();
	
	if(tokensIt->hasMore()) {
		if((*(tokensIt->getValue())).compare("while") == 0) {
			loopType = WHILE;
			tokensIt->next();
		} else if((*(tokensIt->getValue())).compare("until") == 0) {
			loopType = UNTIL;
			tokensIt->next();		
		} else if(Variable::isVariable(*(tokensIt->getValue()))) {
			loopType = FOR;
			
		} else {
			throw RuntimeException("Invalid condition for loop in line " + std::to_string(lineNumber));
		}
	
	} else {
		throw RuntimeException("Expected condition for loop in line " + std::to_string(lineNumber));
	}
	
	std::string conditionStr = "";
	
	while(tokensIt->hasMore()) {
		conditionStr += *(tokensIt->getValue()) + " ";
		tokensIt->next();
	}
	
	if(loopType == FOR) {
		condition = (Line*)(new ForLine(conditionStr, vars, scope + 1));
	} else {
		condition = new Line(conditionStr, vars, scope);
	}
	
	delete tokensIt;
	
	
	lineNumber++;
	
	
	Statement* stmt = nullptr;
	
	do {
		
		stmt = Parser::parse(lines, lineCount, lineNumber, vars, scope + 1);
		statements.add(stmt);
		/*std::cout << (stmt->getType() == Statement::CONTROLSTRUCTUREMOD ? "Yes" : "No");
		std::cout << (stmt->getType() == Statement::CONTROLSTRUCTUREMOD ? std::to_string(((ControlStructureMod*)stmt)->getModType()) : "");
		std::cout << "\t\t\t";
		stmt->print();*/
		
	} while( (stmt->getType() != Statement::CONTROLSTRUCTUREMOD) && (lineNumber < lineCount));
	
	if(lineNumber >= lineCount && stmt->getType() != Statement::CONTROLSTRUCTUREMOD) {
		throw RuntimeException("End of file reached before conditional statement closed");
	}
	
	ControlStructureMod* close = (ControlStructureMod*)statements.getLast();
	
	if(close->getModType() != ControlStructureMod::LOOP) {
		/*std::cout << close->getType() << " " <<"Line: ";
		close->print();
		
		std::cout << "Condition: ";
		condition->print();
		
		print();*/
		
		//close->print();
		
		throw RuntimeException ("Expected token \"loop\" on line " + std::to_string(lineNumber));
	}
	
	close = nullptr;
	
	//std::cout << "Size " << statements.size() << std::endl;
	statements.removeLast();
	
}

void Loop::execute() {
	
	if(loopType == FOR) {
		((ForLine*)condition)->initialize();
	}

	while(evaluateCondition()) {	
		ListIterator<Statement>* it = statements.getIterator();

		while(it->hasMore()) {
			it->getValue()->execute();
			it->next();
		}
		
		delete it;
		if(loopType == FOR)
			((ForLine*)condition)->step();
		
		variables.removeWithScope(scope + 1);
	}
	variables.removeWithScope(scope + 1);
}

bool Loop::evaluateCondition() {
	Variable* result = condition->evaluate();

	if(result->getType() != Types::BOOLEAN)
		throw RuntimeException("Condition must evaluate to BOOLEAN");

	bool* rtnBool = (bool*)(result->getValue());
	
	bool rtn = *rtnBool;
	delete rtnBool;
	
	if(result->getScope() == -1)
		delete result;
	
	return (loopType != UNTIL ? rtn : !rtn); //May lead to errors
	
}

void Loop::print() {
	for(int i = 0; i < scope; i++) {
		std::cout << "\t";
	}
	
	std::cout << "loop ";
	condition->print();
	ListIterator<Statement>* li = statements.getIterator();
	
	while(li->hasMore()) {
		li->getValue()->print();
		li->next();
	}
	
	delete li;
	
	for(int i = 0; i < scope; i++) {
		std::cout << "\t";
	}
	std::cout << "end loop" << std::endl;
}

void Loop::printSimple() {
	std::cout << "loop ";
	condition->print();
}

Loop::~Loop() {
	delete condition;
}
#include "Conditional.hpp"
#include "Parser.hpp"

Conditional::Conditional(ListIterator<std::string>* tokensIt, std::string* lines, int lineCount, int& lineNumber, VariableHashMap& vars, int scope) : ControlStructure(vars, scope, Statement::CONDITIONAL) {
	std::string conditionStr = "";
	tokensIt->next();
	
	while(tokensIt->hasMore()) {
		
		if((*tokensIt->getValue()).compare("then") == 0)
			break;
		conditionStr += *(tokensIt->getValue()) + " ";
		tokensIt->next();
	}
	
	if((*tokensIt->getValue()).compare("then") != 0) {
		throw RuntimeException("Expected token \"then\" on line " + std::to_string(lineNumber));
	}
	
	//std::cout << "Condition: " << conditionStr << std::endl;
	
	condition = new Line(conditionStr, vars, scope + 1);
	
	delete tokensIt;
	
	lineNumber++;
	
	Statement* stmt = nullptr;
	do {
		stmt = Parser::parse(lines, lineCount, lineNumber, vars, scope + 1);
		statements.add(stmt);
	} while( (stmt->getType() != Statement::CONTROLSTRUCTUREMOD) && (lineNumber < lineCount) );
	
	if(lineNumber >= lineCount && stmt->getType() != Statement::CONTROLSTRUCTUREMOD) {
		throw RuntimeException("End of file reached before conditional statement closed");
	}
	
	stmt = nullptr;
	
	ControlStructureMod* close = (ControlStructureMod*)statements.getLast();
	
	if(close->getModType() == ControlStructureMod::LOOP) {
		throw RuntimeException("Expected token \"if\" on line " + std::to_string(lineNumber - 1));
	} else if(close->getModType() == ControlStructureMod::ELSE) {
		elseFlag = true;
		//std::cout << "Else detected" << std::endl;
		do {
			stmt = Parser::parse(lines, lineCount, lineNumber, vars, scope + 1);
			elseStatements.add(stmt);
		} while( (stmt->getType() != Statement::CONTROLSTRUCTUREMOD) && (lineNumber < lineCount) );
		
		if(lineNumber >= lineCount && stmt->getType() != Statement::CONTROLSTRUCTUREMOD) {
			throw RuntimeException("End of file reached before conditional statement closed");
		}
		
		close = (ControlStructureMod*)(elseStatements.getLast());
		if(close->getModType() != ControlStructureMod::CONDITIONAL) {
			throw RuntimeException("Expected token \"if\" on line " + std::to_string(lineNumber - 1));
		}
		elseStatements.removeLast();
		
	}
	
	statements.removeLast();
	
	
	close = nullptr;

}

void Conditional::execute() {
	ListIterator<Statement>* it;
	if(evaluateCondition()) { //Replace later with EvaluateCondition
		it = statements.getIterator();
	} else if(elseFlag == true) {
		it = elseStatements.getIterator();
	} else {
		return;
	}
	
	while(it->hasMore()) {
		it->getValue()->execute();
		it->next();
	}
	
	delete it;
	
	variables.removeWithScope(scope + 1);
}

void Conditional::print() {
	
	for(int i = 0; i < scope; i++) {
		std::cout << "\t";
	}
	
	std::cout << "if ";
	condition->print();
	ListIterator<Statement>* li = statements.getIterator();
	
	while(li->hasMore()) {
		li->getValue()->print();
		li->next();
	}
	
	delete li;
	
	if(elseFlag) {
		for(int i = 0; i < scope; i++) {
			std::cout << "\t";
		}
		std::cout << "else" << std::endl;
		
		li = elseStatements.getIterator();
		
		while(li->hasMore()) {
			li->getValue()->print();
			li->next();
		}
		
		delete li;
		
	}
	
	for(int i = 0; i < scope; i++) {
		std::cout << "\t";
	}
	std::cout << "end if" << std::endl;
}

void Conditional::printSimple() {
	std::cout << "if ";
	condition->print();
	
	if(elseFlag) {
		std::cout << "\t" << "else";
	}
	
	 std::cout << std::endl;
}

bool Conditional::evaluateCondition() {
	
	Variable* result = condition->evaluate();
	
	if(result->getType() != Types::BOOLEAN)
		throw RuntimeException("Condition must evaluate to BOOLEAN");

	bool* rtnBool = (bool*)(result->getValue());
	
	bool rtn = *rtnBool;


	//Dubious uncommenting
	//delete rtnBool;
	
	if(result->getScope() == -1)
		delete result;
	
	return rtn;
}

Conditional::~Conditional() {
	delete condition;
}

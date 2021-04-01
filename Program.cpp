#include "Program.hpp"

Program::Program(std::string* lines, int lineCount) : Segment(*(new VariableHashMap()), 0, Statement::PROGRAM){
	
	int lineNumber = 0;	
	
	while(lineNumber < lineCount) {
		try {
			statements.add(Parser::parse(lines, lineCount, lineNumber, variables, scope));
		} catch(ListException&) {
			std::cout << "Exception caught in program" << std::endl;
			std::cout << lineCount << std::endl;
		}
	}
	
	//print();	
	execute();
	
	
}

Program::~Program() {
	delete &variables;
}

void Program::execute() {
	ListIterator<Statement>* it = statements.getIterator();
	
	while(it->hasMore()) {
		it->getValue()->execute();
		it->next();
	}
	
	delete it;
}

void Program::print() {
	ListIterator<Statement>* sIt = statements.getIterator();
	
	while(sIt->hasMore()) {
		sIt->getValue()->print();
		sIt->next();
	}
	
	delete sIt;
}
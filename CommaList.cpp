#include "CommaList.hpp"

CommaList::CommaList(Variable* var1, Variable* var2) : Variable(nullptr, Types::COMMALIST, -2) {
	
	if(var1->getScope() == -1)
		internalVariables.add(new Variable(var1));
	else
		internalVariables.add(var1);
	
	
	if(var2->getScope() == -1)
		internalVariables.add(new Variable(var2));
	else
		internalVariables.add(var2);
	
}

CommaList::~CommaList() {
	ListIterator<Variable>* it = internalVariables.getIterator();
	
	while(it->hasMore()) {
		if(it->getValue()->getScope() == -1) {
			delete it->getValue();
			it->setValue(nullptr);
		}
		
		it->next();
	}
	
	delete it;
	
	internalVariables.clearWithoutDeletingContents();
}

void CommaList::add(Variable* var) {
	if(var->getScope() == -1)
		internalVariables.add(new Variable(var));
	else
		internalVariables.add(var);
}

void CommaList::print() {
	ListIterator<Variable>* it = internalVariables.getIterator();
	
	while(it->hasMore()) {
		it->getValue()->print();
		it->next();
	}
	
	delete it;
	
	std::cout << std::endl;
}
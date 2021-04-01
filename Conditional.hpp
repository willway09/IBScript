#ifndef _CONDITIONAL_HPP
#define _CONDITIONAL_HPP

#include "ControlStructure.hpp"

class Conditional : public ControlStructure {
	private:
		SinglyLinkedList<Statement> elseStatements;
		bool elseFlag = false;
	
	public:
		Conditional(ListIterator<std::string>* tokensIt, std::string* lines, int lineCount, int& lineNumber, VariableHashMap& vars, int scope);
		~Conditional();
		
		void execute();
		void print();
		void printSimple();
		bool evaluateCondition();
};

#endif //_CONDITIONAL_HPP
#ifndef _LOOP_HPP
#define _LOOP_HPP

#include "ControlStructure.hpp"
#include "Parser.hpp"
#include "ForLine.hpp"

class Loop : public ControlStructure {
	private:
		enum LoopType {
			UNTIL, WHILE, FOR
		};
		
		LoopType loopType;
	public:
		Loop(ListIterator<std::string>* tokensIt, std::string* lines, int lineCount, int& lineNumber, VariableHashMap& vars, int scope);
		~Loop();
		
		void execute();
		void print();
		void printSimple();
		bool evaluateCondition();
		
};

#endif //_LOOP_HPP
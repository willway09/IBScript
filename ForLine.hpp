#ifndef _FORLINE_HPP
#define _FORLINE_HPP

#include "VariableHashMap.hpp"
#include "Line.hpp"

class ForLine : Line {
	private:
		Variable* loopVar = nullptr;
		VariableName* loopVarName = nullptr;
		static const std::regex forLineRegex;
		Line* initializationLine = nullptr;
	
	public:
		ForLine(std::string line, VariableHashMap& vars, int scope);
		~ForLine();
		
		void execute();
		Variable* evaluate();
		void print();
		void printSimple();
		
		void step();
		void initialize();
};

#endif //_FORLINE_HPP
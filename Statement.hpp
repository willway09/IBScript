#ifndef _STATEMENT_HPP
#define _STATEMENT_HPP

#include "VariableHashMap.hpp"

class Statement {
	public:
		enum StatementType {
			LINE, PROGRAM, LOOP, CONDITIONAL, CONTROLSTRUCTUREMOD
		};
	
	protected:
		int scope;
		StatementType type;
		VariableHashMap& variables;
		Statement(VariableHashMap& vars, int s, StatementType t) : variables(vars), scope(s), type(t) { }
		
	public:
		virtual void execute() = 0;
		virtual void print() = 0;
		virtual void printSimple() = 0;
		
		StatementType getType() { return type; }
};

#endif //_STATEMENT_HPP
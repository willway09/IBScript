#ifndef _LINE_HPP
#define _LINE_HPP

#include "Statement.hpp"
#include <string>
#include <iostream>

#include "DataStructures/PriorityQueue.hpp"

#include "Operator.hpp"
#include "Tokenizer.hpp"
#include "Variable.hpp"

class Line : public Statement {
	protected:
		std::string line;
	private:
		Variable* evaluateRecursive(PriorityQueue<Operator>& opQueue, SinglyLinkedList<std::string>& tokens, VariableHashMap& variables, int min, int max, int scope);
		void evaluate(std::string& line, VariableHashMap& variables, Variable** rtn);
		
	public:
		Line(std::string ln, VariableHashMap& vars, int scope) : line(ln), Statement(vars, scope, Statement::LINE) {}
		void execute();
		void print();
		void printSimple() {
			print();
		}
		
		virtual Variable* evaluate();
};

#endif //_LINE_HPP
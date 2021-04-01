#ifndef _OPERATOR_HPP
#define _OPERATOR_HPP

#include "Types.hpp"
#include <regex>
#include "RuntimeException.hpp"
#include "Variable.hpp"
#include "CommaList.hpp"

class Operator {
	public:
		enum OperatorType {
			ASSIGN=0,
			ADD, SUB, MULT, DIV, MOD,
			NEG,
			AND, OR, NOT,
			LT, GT, LTE, GTE, NEQ, EQ,
			DOT, COMMA, ARRAY
		};
		
		static const std::regex operatorRegex;
		
	private:
		int precedence;
		int index;
		int depth;
		OperatorType type;
		
	public:
		Operator(std::string* op, std::string* before, int idx, int dpt);
		
		int getIndex() { return index; }
		int getDepth() { return depth; }
		int getPrecedence() { return precedence; }
		
		static bool isOperator(std::string& op) {
			if(op.compare("AND")==0 || op.compare("OR")==0 || op.compare("NOT")==0) return true;
			else if(op.compare("div")==0 || op.compare("mod") == 0) return true;
			else if(op.front() == '"' && op.back() == '"') return false;
			else return std::regex_match(op, operatorRegex);
		}
		
		Variable* evaluate(Variable* var1, Variable* var2);
		
		int compare(Operator& otherOp);
		
		void printDetails();
		void print();
		
};

#endif //_OPERATOR_HPP
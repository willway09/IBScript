#ifndef _PARSER_HPP
#define _PARSER_HPP

#include "Statement.hpp"
#include "Line.hpp"
#include "ControlStructure.hpp"
#include "Loop.hpp"
#include "Conditional.hpp"
#include "ControlStructureMod.hpp"

#include <string>

class Parser {
	public:
		static Statement* parse(std::string* lines, int lineCount, int& lineNumber, VariableHashMap& vars, int scope);
};

#endif //_PARSER_HPP
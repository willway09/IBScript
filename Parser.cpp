#include "Parser.hpp"
#include "Tokenizer.hpp"
#include <regex>

Statement* Parser::parse(std::string* lines, int lineCount, int& lineNumber, VariableHashMap& vars, int scope) {
	
	if(lineNumber >= lineCount) return (Statement*)(new Line("", vars, scope));
	
	SinglyLinkedList<std::string> tokens;
	
	Tokenizer::tokenize(lines[lineNumber], tokens);
	
	if(tokens.size() > 0) {
		
		
		if(tokens.getFirst()->compare("loop") == 0) {
			return (Statement*)(new Loop(tokens.getIterator(), lines, lineCount, lineNumber, vars, scope));
		} else if(tokens.getFirst()->compare("if") == 0) {
			return (Statement*)(new Conditional(tokens.getIterator(), lines, lineCount, lineNumber, vars, scope));
		} else if(tokens.getFirst()->compare("end") == 0) {
			if(tokens.size() == 2) {
				lineNumber++;
				return (Statement*)(new ControlStructureMod(*(tokens.get(1)), vars, scope));
			} else {
				throw RuntimeException("Expected two tokens on line " + std::to_string(--lineNumber));
			}
			
		} else if(tokens.getFirst()->compare("else") == 0) {
			lineNumber++;
			return (Statement*)(new ControlStructureMod(*(tokens.getFirst()), vars, scope));
		} else {
			return (Statement*)(new Line(lines[lineNumber++], vars, scope));
		}
		
	} else {
		//std::cout << "Error" << std::endl;
		
		lineNumber++;
		return parse(lines, lineCount, lineNumber, vars, scope);
	}
}
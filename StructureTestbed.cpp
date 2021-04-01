#include "ControlStructure.hpp"
#include "Line.hpp"
#include "Parser.hpp"
#include "Program.hpp"

#include <string>

int main() {
	int size = 7;
	std::string* lines = new std::string[size];
	
	lines[0] = "A = 1";
	lines[1] = "B = 1";
	lines[2] = "if A==B";
	lines[3] = "	output A - B";
	lines[4] = "else";
	lines[5] = "	output B + A";
	lines[6] = "end if";
	
	Program* prg = new Program(lines, size);
	
	delete[] lines;
	return 0;
}
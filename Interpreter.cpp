#include <iostream>
#include <fstream>
#include <string>
#include "DataStructures/SinglyLinkedList.hpp"

#include <regex>
#include <random>
#include "Program.hpp"
#include <cstdlib>

int main(int argc, char** argv) {
	
	std::string fileName;
	
	if(argc != 2) {
		std::cout << "Please run with the following form: " << std::endl;
		std::cout << "ibscript.exe <filename>" << std::endl;
		std::cout << std::endl;
		std::cout << "For an IDE, please run IBScript.jar using:" << std::endl;
		std::cout << "java -jar IBScript.jar" << std::endl;
		
		std::exit(1);
	} else {
		fileName = argv[1];
	}
	
	std::ifstream file(fileName);
	std::string line;
	
	
	
	//std::regex whitespace("^\\s*$");
	
	SinglyLinkedList<std::string> linesList;
	std::string* lines;
	int linesCount;

	while(!file.eof()) {
		std::getline(file, line);
		//std::cout << line << std::endl;
		linesList.add(new std::string(line));
	}
	
	file.close();
	
	linesCount = linesList.size();
	lines = new std::string[linesCount];
	
	//linesList->extractToArray(lines);
	
	ListIterator<std::string>* lIt = linesList.getIterator();
	
	int idx = 0;
	
	while(lIt->hasMore()) {
		
		lines[idx] = *(lIt->getValue());
		
		idx++;
		lIt->next();
	}

	Program prg(lines, linesCount);
	
	//variables.status();
	
	delete[] lines;
	
}
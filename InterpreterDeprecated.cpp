#include <iostream>
#include <fstream>
#include <string>
#include "Tokenizer.hpp"
#include "DataStructures/SinglyLinkedList.hpp"
#include "DataStructures/PriorityQueue.hpp"
#include "DataStructures/Stack.hpp"
#include "VariableHashMap.hpp"

#include "Variable.hpp"
#include "Operator.hpp"

#include <regex>
#include <random>
#include "Loop.hpp"

enum SeekMode {
	NORMAL, NEXT_LOOP, NEXT_IF
};

Variable* evaluateRecursive(PriorityQueue<Operator>& opQueue, SinglyLinkedList<std::string>& tokens, VariableHashMap& variables, int min, int max, int scope) {

	
	//std::cout << "Max: " << max << " Min: " << min << std::endl;
	
	if(max == min) {
		//std::cout << "Going Here " << max << std::endl;
		try {
		std::string token = *(tokens.get(min));
					
		Variable* rtn = nullptr;
		if(Variable::isVariable(token)) {
			VariableName* temp = new VariableName(token);
			if(variables.containsKey(temp)) {
				return variables.get(temp);
			} else {
				rtn = new Variable(nullptr, Types::OTHER, scope);
				variables.add(new VariableName(token), rtn);
				return rtn;
			}
			delete temp;
		} else {

			
			Types::TypeName t = Types::determineType(token);

			
			switch(t) {
				case Types::INT:
					rtn = new Variable(new int(std::stoi(token)), t, -1);
					break;
				case Types::DOUBLE:
					rtn = new Variable(new double(std::stod(token)), t, -1);
					break;
				case Types::BOOLEAN:
				
					if(token.compare("true")==0) {
						rtn = new Variable(new bool(true), t, -1);
					} else {
						rtn = new Variable(new bool(false), t, -1);
					}

					break;
				case Types::STRING:
					rtn = new Variable(new std::string(token.substr(1, token.length() - 2)), t, -1);
					break;
			}
				
			
		}
		return rtn;
		
		} catch(ListException&) {
			return nullptr;
		}
	} else {
		
		Operator* op = opQueue.dequeue();
		
		PriorityQueue<Operator> upper;
		PriorityQueue<Operator> lower;

		
		while(opQueue.size() > 0) {
			Operator* temp = opQueue.dequeue();
			if(temp->getIndex() > op->getIndex()) {
				upper.enqueue(temp);
			} else {
				lower.enqueue(temp);
			}
		}

		Variable* a = evaluateRecursive(lower, tokens, variables, min, op->getIndex() - 1, scope);
		Variable* b = evaluateRecursive(upper, tokens, variables, op->getIndex() + 1, max, scope);
		

		Variable* rtn = op->evaluate(a, b);
		
		if(a->getScope() == -1) delete a;
		if(b->getScope() == -1) delete b;		
		
		delete op;
		return rtn;

	}

}

void evaluate(std::string& line, int& lineNumber, VariableHashMap& variables, Stack<Loop>& loopStack, int& seekMode) {
		
	SinglyLinkedList<std::string> tokens;
	Tokenizer::tokenize(line, tokens);
	
	PriorityQueue<Operator> opQueue;
	
	int loopEvaluationFlag = 0;
	int outputFlag = 0;
	
	if(tokens.getFirst()->compare("loop")==0) {
		tokens.removeHead();
		
		if(tokens.getFirst()->compare("while")==0) {
			tokens.removeHead();
			loopEvaluationFlag = 1;
			if(loopStack.top()->getStartLine() != lineNumber) loopStack.push(new Loop(loopStack.top()->getScope() + 1, lineNumber));
		} else if(tokens.getFirst()->compare("until")==0) {
			tokens.removeHead();
			loopEvaluationFlag = -1;
			if(loopStack.top()->getStartLine() != lineNumber) loopStack.push(new Loop(loopStack.top()->getScope() + 1, lineNumber));
		} else {
			throw RuntimeException("Expected while or until in loop");
		}
		
	}
	
	if(tokens.getFirst()->compare("end")==0) {
		tokens.removeHead();
		
		if(tokens.getFirst()->compare("loop")==0) {
			tokens.removeHead();
			
			if(seekMode == NEXT_LOOP) {
				seekMode = NORMAL;
			} else {
				lineNumber = loopStack.top()->getStartLine() - 1;
			}
			return;
		} else {
			throw RuntimeException("Expected loop in end");
		}
	} else if(seekMode == NEXT_LOOP) {
		return;
	}
	
	if(tokens.getFirst()->compare("output") == 0) {
		outputFlag = 1;
		tokens.removeHead();
	}
	
	//std::cout << "Line: " << lineNumber << " Token Count: " << tokens.size() << std::endl;
	
	
	
	ListIterator<std::string>* tokensIt = tokens.getIterator();
	
	int idx = 0;
	int depth = 0;
	
	std::string* before = nullptr;
	
	if(tokens.size() > 1) {
		while(tokensIt->hasMore()) {
			if(tokensIt->getValue()->compare("(")==0) {
				tokensIt->next();
				tokens.removeAt(idx);
				//idx--;
				depth++;
				continue;
			} else if(tokensIt->getValue()->compare(")")==0) {
				tokensIt->next();
				tokens.removeAt(idx);
				//idx--;
				depth--;
				continue;
			} else {
				if(Operator::isOperator(*(tokensIt->getValue()))) {
					//std::cout << *(tokensIt->getValue()) << std::endl;
					
					opQueue.enqueue(new Operator(new std::string(*(tokensIt->getValue())), before, idx, depth));
				}
			}
			
			before = tokensIt->getValue();
			tokensIt->next();
			idx++;
			
			//std::cout << "Doint things " << lineNumber << std::endl;
		}

		
		opQueue.prioritize();
	}
		
	delete tokensIt;
	
	/*while(opQueue.size() > 0) {
		Operator* temp = opQueue.dequeue();
		temp->printDetails();
		std::cout << std::endl;
		delete temp;
	}*/
	
	if(depth != 0) {
		throw RuntimeException("Uneven number of parenthese!");
	}
	
	//tokens.print();

	
	Variable* result = evaluateRecursive(opQueue, tokens, variables, 0, tokens.size() - 1, loopStack.top()->getScope());
	
	if(loopEvaluationFlag != 0) {
		
		if(result->getType() == Types::BOOLEAN) {					
			if(loopEvaluationFlag == 1) {
				if(*(bool*)(result->getValue()) == false) {
					seekMode = NEXT_LOOP;
					Loop* temp = loopStack.pop();
					variables.removeWithScope(temp->getScope());
					delete temp;
				}
			} else if(loopEvaluationFlag == -1) {
				if(*(bool*)(result->getValue()) == true) {
					seekMode = NEXT_LOOP;
					Loop* temp = loopStack.pop();
					variables.removeWithScope(temp->getScope());
					delete temp;
				}
			}
		} else {
			throw RuntimeException("Must evaluate to a BOOLEAN");
		}
			
	}
	
	if(outputFlag != 0) {
		result->print();
		std::cout << std::endl;
	}
	
	if(result->getScope() == -1) delete result;
	
}

int main(int argc, char** argv) {
	
	if(argc < 2) return -1;
	
	std::ifstream file(argv[1]);
	std::string line;
	
	std::regex whitespace("^\\s*$");
	
	VariableHashMap variables;
	Stack<Loop> loopStack;
	loopStack.push(new Loop(0, -1));
	
	SinglyLinkedList<std::string>* linesList = new SinglyLinkedList<std::string>();
	std::string** lines;
	int linesCount;

	while(!file.eof()) {
		std::getline(file, line);
		//std::cout << line << std::endl;
		linesList->add(new std::string(line));
	}
	
	file.close();
	
	linesCount = linesList->size();
	lines = new std::string*[linesCount];
	
	linesList->extractToArray(lines);
	
	delete linesList;
	
	
	
	int seekMode = NORMAL;
	for(int i = 0; i < linesCount; i++) {
		//std::cout << "I: " << i << std::endl;
		if(!std::regex_match(*(lines[i]), whitespace))
			evaluate(*(lines[i]), i, variables, loopStack, seekMode);
	}
	
	//variables.status();
	
	for(int i = 0; i < linesCount; i++) {
		delete lines[i];
	}
	
	delete lines;
	
	
	
	
	
	
	/*std::cout << std::endl << std::endl << std::endl << "Press ENTER to continue: ";
	char* ch;
	
	std::cin.getline(ch,1);*/
	
	
	
	
	//=================================================================================================================
	
	
	
	/*std::string test = "+";
	
	std::regex stringRegex("^\\\".*\\\"$");
	std::regex intRegex("^\\d+$");
	std::regex variableRegex("^[A-Z]+$");
	std::regex operatorRegex("[^a-zA-Z\\d\\s]");
	
	std::cout << test << std::endl;
	std::cout << std::regex_match(test, operatorRegex);*/
	
	/*VariableHashMap variables;
	
	int twoCount = 0;
	
	for(int i = 0; i < 50; i++) {
		int scp = std::rand() % 3; 
		
		if(scp==2) twoCount++;
		
		variables.add(
			new VariableName(std::to_string(std::rand())),
			new Variable((void*)(new int(std::rand())), Types::INT, scp)
		);
	}
	
	variables.printVariables();
	std::cout << "==========================" << std::endl;
	std::cout << "Old Size: " << variables.getContentsCount() << std::endl;
	variables.removeWithScope(2);
	std::cout << "New Size: " << variables.getContentsCount() << std::endl;
	std::cout << "Count: " << twoCount << std::endl;
	std::cout << "==========================" << std::endl;
	variables.printVariables();*/
	
	
}
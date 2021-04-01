#include "Line.hpp"
#include "DataStructures/Stack.hpp"
#include "RuntimeException.hpp"

Variable* Line::evaluateRecursive(PriorityQueue<Operator>& opQueue, SinglyLinkedList<std::string>& tokens, VariableHashMap& variables, int min, int max, int scope) {

	
	//std::cout << "Max: " << max << " Min: " << min << std::endl;
	
	if(max == min) {
		//std::cout << "Going Here " << max << std::endl;
		try {
			std::string token = *(tokens.get(min));
						
			Variable* rtn = nullptr;
			
			if(token.compare("") ==0) return rtn;
			
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
				case Types::LANGUAGEELEMENT:
					rtn = new Variable(new std::string(token), t, -1);
					break;
			}
				
			
		}
		return rtn;
		
		} catch(ListException&) {
			return nullptr;
		}
	} else {
		
		if(opQueue.size() == 0) return nullptr;
		
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
		
		if(a != nullptr) {
			if(a->getScope() == -1) {
				delete a;
			}
		}
		
		if(b != nullptr) {
			if(b->getScope() == -1) {
				delete b;
			}
		}
			
		delete op;
		return rtn;

	}

}

void Line::evaluate(std::string& line, VariableHashMap& variables, Variable** rtn = nullptr) {
	
	SinglyLinkedList<std::string> tokens;
	Tokenizer::tokenize(line, tokens);
	
	if(tokens.size() == 0) return;
	
	PriorityQueue<Operator> opQueue;

	int outputFlag = 0;
	
	if(tokens.getFirst()->compare("output") == 0) {
		outputFlag = 1;
		tokens.removeHead();
	}
	
	
	ListIterator<std::string>* tokensIt = tokens.getIterator();
	
	int idx = 0;
	int depth = 0;
	
	std::string* before = nullptr;
	
	Stack<char> bracketStack;
	
	
	if(tokens.size() > 1) {
	
		std::string* openParen = new std::string("(");
		std::string* closeParen = new std::string(")");
		std::string* openBracket = new std::string("[");
		std::string* closeBracket = new std::string("]");
		
		while(tokensIt->hasMore()) {
			
			if(tokensIt->getValue()->compare("(")==0) {

				if(before != nullptr) {
					if(Types::isLanguageElement(*before)) {
						
						std::string* dot = new std::string(".");
						
						tokens.insertAfter(idx, dot);
						opQueue.enqueue(new Operator(dot, before, idx, depth));
					}
				}
				
				tokensIt->next();
				tokens.removeAt(idx); //Remove open parenthese

				
				bracketStack.push(new char('('));
				before = openParen;
				depth++;
				continue;
			} else if(tokensIt->getValue()->compare(")")==0) {
				tokensIt->next();
				tokens.removeAt(idx); //Remove close parenthese
				
				if(before == openParen) {
					tokens.insertAt(idx, new std::string(""));
					idx++;
					std::cout << "Adding" << std::endl;
				}
							
				try {	
					char* bracket = bracketStack.pop();
					if(*bracket != '(') throw RuntimeException("Expected closing parenthese");
					
					delete bracket;
				} catch(ListException&) {
					throw RuntimeException("Expected opening parehthese");
				}
				
				before = closeParen;

				depth--;
				continue;
				
			} else if(tokensIt->getValue()->compare("[")==0) {
				opQueue.enqueue(new Operator(new std::string(*(tokensIt->getValue())), before, idx, depth));
				bracketStack.push(new char('['));
				before = openBracket;
				depth++;
				idx++;
				tokensIt->next();
				continue;
			} else if(tokensIt->getValue()->compare("]")==0) {
				tokensIt->next();
				tokens.removeAt(idx); //Remove close bracket
				if(before == openBracket) {
					tokens.insertAt(idx, new std::string(""));
					idx++;
				}
				
				try {
					char* bracket = bracketStack.pop();
					
					if(*bracket != '[') throw RuntimeException("Expected closing bracket");
					
					delete bracket;
				} catch(ListException&) {
					throw RuntimeException("Expected opening bracket");
				}
				before = closeBracket;

				depth--;
				continue;
				
			} else {
				
				if(Operator::isOperator(*(tokensIt->getValue()))) {					
					opQueue.enqueue(new Operator(new std::string(*(tokensIt->getValue())), before, idx, depth));
				}
			}
			
			before = tokensIt->getValue();
			tokensIt->next();
			idx++;
			
		}
		
		if(opQueue.size() > 0)
			opQueue.prioritize();
		
		//std::cout << "Prioritization failed" << std::endl;
		
		
		
				
		delete tokensIt;
		
		delete openParen;
		delete closeParen;
		delete openBracket;
		delete closeBracket;
		
	} else if(tokens.size() == 0) {
		return;
	}
	
	
	
	
	/*int queueSize = opQueue.size();
	std::cout << "opQueue size: " << opQueue.size() << std::endl;
	for(int i = 0; i < opQueue.size(); i++) {
		Operator* op = opQueue.dequeue();
		op->printDetails();
		opQueue.enqueue(op);
	}
	std::cout << std::endl;
	/*
	auto iterator = tokens.getIterator();
	while(iterator->hasMore()) {
		std::cout << '"' << *(iterator->getValue()) << '"' << std::endl;
		iterator->next();
	}

		std::exit(0);*/
		
		
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
	
	Variable* result = evaluateRecursive(opQueue, tokens, variables, 0, tokens.size() - 1, scope);
	
	if(outputFlag != 0) {
		result->print();
		std::cout << std::endl;
	}
	
	if(rtn != nullptr) {
		*rtn = result;
	}
	else if(result->getScope() == -1)
		delete result;
	
}

void Line::execute() {
	//Populate me
	evaluate(line, variables);

}

Variable* Line::evaluate() {
	Variable* rtn = nullptr;
	evaluate(line, variables, &rtn);
	return rtn;
}

void Line::print() {
	std::cout << line << std::endl;
}
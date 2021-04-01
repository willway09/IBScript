#include "Tokenizer.hpp"

int main() {
	std::string s1 = "   Hello \nWorld   I	\tAm ReadyB 1+((1\n";
	
	SinglyLinkedList<std::string> tokens;
	
	Tokenizer::tokenize(s1, tokens);
	
	tokens.print();
}
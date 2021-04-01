#ifndef _TOKENIZER_HPP
#define _TOKENIZER_HPP

#include <iostream>
#include <string>
#include <cctype>

#include "DataStructures/SinglyLinkedList.hpp"

class Tokenizer {
	private:		
		static int getCharType(char c) {
			//Returns 0 if whitespace, 1 if operator, 2 if bracket, and 3 if alphanumeric
			//These correspond to values in the CharTypes enumeration
			
			if ( (c == 40) || (c == 41) || (c == 91) || (c == 93) || (c == 123) || (c == 125) ) {
				return 2;
			} else {
				return 2 * (std::isalnum(c) ? 1 : 0) + (!std::isspace(c) ? 1 : 0);
			}


		}
		
		enum CharTypes {
			WHITESPACE = 0, OPERATOR, BRACKET, ALPHANUMERIC
		};
		
	public:
		static void tokenize(std::string& base, SinglyLinkedList<std::string>& tokens) {
			//std::string* token = new std::string();
			
			std::string::iterator it=base.begin();

			while(it != base.end()) {
				if(std::isspace(*it)) {
					while(getCharType(*it) == 0 && (it != base.end())) {
						++it;
					}
				} else if(getCharType(*it) == BRACKET) {
					tokens.add(new std::string(1, *it));
					++it;
				} else if(*it == '"') {
					std::string* token = new std::string();
					token->append(1, *it);
					++it;
					while((*it != '"') && (it != base.end())) {
						token->append(1,*it);
						++it;
					}
					token->append(1, *it);
					++it;
					tokens.add(token);
				} else {
					
					std::string* token = new std::string();
					int initialCharType = getCharType(*it);
					
					while((getCharType(*it) == initialCharType) && (it != base.end())) {
						token->append(1,*it);	
						++it;
					}
					
					if(token->find("//") != std::string::npos) return;
					
					tokens.add(token);
				}

			}
		}
};

#endif //_TOKENIZER_HPP

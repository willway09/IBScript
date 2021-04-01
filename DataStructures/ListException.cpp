#include "ListException.hpp"
#include <cstdio>
#include <iostream>

const char* ListException::what() const throw() {
	return returnString->c_str();
}

ListException::ListException(ExceptionType tp, int length, int idx) : type(tp), listLength(length), index(idx) {
	switch(type) {
		case OUT_OF_BOUNDS:			
			returnString = new std::string(std::string("Cannot access position outside of list range (Size: ") + std::to_string(listLength)
				+ std::string(", Index: ") + std::to_string(index)
				+ std::string(")"));
			break;
		case DUPLICATE:
			returnString = new std::string(std::string("Cannot add duplicate pointers to list (Size: ") + std::to_string(listLength) + std::string(")"));
			break;
	}
	
	//std::cout << *returnString << std::endl;
}

ListException::~ListException() {
	delete returnString;
}
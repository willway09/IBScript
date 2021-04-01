#ifndef _TESTEXCEPTION_HPP
#define _TESTEXCEPTION_HPP

#include <exception>

class TestException : public std::exception {
	
	virtual const char* what() {
		return "An exception has been thrown";
	}
	
	public:
		int a = 0;
};

#endif //_TESTEXCEPTION_HPP
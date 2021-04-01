#ifndef _RUNTIMEEXCEPTION_HPP
#define _RUNTIMEEXCEPTION_HPP

#include <exception>
#include <string>

class RuntimeException : public std::exception {
	private:
		std::string* description;
		
	public:
		RuntimeException(const std::string& s) {
			description = new std::string(s);
		}
		
		virtual const char* what() const throw() {
			return description->c_str();
		}
		
		~RuntimeException() {
			delete description;
		}


};

#endif //_RUNTIMEEXCEPTION_HPP
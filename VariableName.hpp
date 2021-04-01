#ifndef _VARIABLENAME_HPP
#define _VARIABLENAME_HPP

#include <string>
#include <iostream>

class VariableName : public std::string {
	public:
		int hashCode();
		bool equals(VariableName* vn);
		
		VariableName(std::string s) : std::string(s) {}
};

#endif //_VARIABLENAME_HPP
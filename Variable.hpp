#ifndef _VARIABLE_HPP
#define _VARIABLE_HPP

#include "Types.hpp"
#include <iostream>

class Variable {
	private:
		void* value = nullptr;

		int scope;
		
		void deleteValue();
		
		static const std::regex variableRegex;
		
	protected:
		Types::TypeName type;
	
	public:
		Variable(void* v, Types::TypeName t, int s);
		Variable(Variable* var);
		~Variable();

		void* getValue() {
			return value;
		}
		
		void setValue(void* v) {
			deleteValue();
			value = v;
		}
		
		Types::TypeName getType() {
			return type;
		}
		
		virtual void setType(Types::TypeName t);
		
		static bool isVariable(std::string& s) {
			if(s.compare("AND")==0 || s.compare("OR")==0 || s.compare("NOT")==0) return false;
			return std::regex_match(s, variableRegex);
		}
		
		int getScope() {
			return scope;
		}
		
		void printDetails();
		virtual void print();
};

#endif //_VARIABLE_HPP
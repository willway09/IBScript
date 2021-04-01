#ifndef _VARIABLEHASHMAP_HPP
#define _VARIABLEHASHMAP_HPP

#include "Variable.hpp"
#include "VariableName.hpp"
#include "DataStructures/HashMap.hpp"

#include <iostream>

class VariableHashMap : public HashMap<VariableName, Variable> {
	public:
		void removeWithScope(int s);
		
		void printVariables();
		
};

#endif //_VARIABLEHASHMAP_HPP
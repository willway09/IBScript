#ifndef _COMMALIST_HPP
#define _COMMALIST_HPP

#include "Variable.hpp"
#include "DataStructures/SinglyLinkedList.hpp"


class CommaList : public Variable {
	private:
		SinglyLinkedList<Variable> internalVariables;
		
	public:
		CommaList(Variable* var1, Variable* var2);
		~CommaList();
		
		void add(Variable* var);
		void print();
		
};

#endif //_COMMALIST_HPP
#ifndef _SEGMENT_HPP
#define _SEGMENT_HPP

#include "Statement.hpp"

#include "DataStructures/SinglyLinkedList.hpp"

class Segment : public Statement {
	protected:
		SinglyLinkedList<Statement> statements;
		Segment(VariableHashMap& var, int scope, Statement::StatementType type) : Statement(var, scope, type) { }
		
	public:
		
		~Segment() { } 
		
};

#endif //_SEGMENT_HPP
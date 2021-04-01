#ifndef _CONTROLSTRUCTURE_HPP
#define _CONTROLSTRUCTURE_HPP

#include "Statement.hpp"
#include "Line.hpp"
#include "Segment.hpp"
#include "VariableHashMap.hpp"
#include "DataStructures/SinglyLinkedList.hpp"


class ControlStructure : public Segment {
	protected:
		Line* condition;
	
	public:
		ControlStructure(VariableHashMap& var, int scope, Statement::StatementType type) : Segment(var, scope, type) { }
		
		virtual bool evaluateCondition() = 0;
	
			
};

#endif //_CONTROLSTRUCTURE_HPP
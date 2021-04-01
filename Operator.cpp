#include "Operator.hpp"
#include "Object.hpp"
#include "Array.hpp"
#include "LanguageCollection.hpp"
#include "LanguageStack.hpp"
#include "LanguageQueue.hpp"
#include <iostream>
#include <cstdlib>

Variable* assignOp(Variable* var1, Variable* var2) {
	
	Types::TypeName t = var2->getType();
	
	Variable* rtn;
	
	if(t == Types::INT) {
		var1->setValue(new int(*(int*)(var2->getValue())));
		var1->setType(var2->getType());
		rtn = new Variable((void*)new int(*(int*)(var1->getValue())), var1->getType(), -1);
	} else if( t == Types::DOUBLE) {
		var1->setValue(new double(*(double*)(var2->getValue())));
		var1->setType(var2->getType());
		rtn = new Variable((void*)new double(*(double*)(var1->getValue())), var1->getType(), -1);
	} else if( t == Types::BOOLEAN) {
		var1->setValue(new bool(*(bool*)(var2->getValue())));
		var1->setType(var2->getType());
		rtn = new Variable((void*)new bool(*(bool*)(var1->getValue())), var1->getType(), -1);
	} else if( t == Types::STRING) {
		var1->setValue(new std::string(*(std::string*)(var2->getValue())));
		var1->setType(var2->getType());
		rtn = new Variable((void*)new std::string(*(std::string*)(var1->getValue())), var1->getType(), -1);
	} else if(t == Types::OBJECT) {
		var1->setValue(var2->getValue());
		((Object*)var1->getValue())->createReference();
		var1->setType(t);
		rtn = new Variable(var1->getValue(), t, -1);
	} else if( t== Types::COMMALIST) {
		throw RuntimeException("Cannot assign a Comma List to a variable");
	}
	
	return rtn;
}

Variable* negOp(Variable* var1, Variable* var2) {
	if(var2->getType() == Types::INT) {
		return new Variable(
			new int(-*(int*)(var2->getValue())),
			Types::INT,
			-1
		);
	} else {
		throw RuntimeException("Negation requires an INT");
	}
}

Variable* addOp(Variable* var1, Variable* var2) {
	
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new int(*(int*)(var1->getValue()) + *(int*)(var2->getValue())),
			Types::INT,
			-1
		);
	} else {
		throw RuntimeException("Addition requires two INTS");
	}
}

Variable* subOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new int(*(int*)(var1->getValue()) - *(int*)(var2->getValue())),
			Types::INT,
			-1
		);
	} else {
		throw RuntimeException("Subtraction requires two INTS");
	}
}

Variable* multOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new int(*(int*)(var1->getValue()) * *(int*)(var2->getValue())),
			Types::INT,
			-1
		);
	} else {
		throw RuntimeException("Multiplication requires two INTS");
	}
}

Variable* divOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new int(*(int*)(var1->getValue()) / *(int*)(var2->getValue())),
			Types::INT,
			-1
		);
	} else {
		throw RuntimeException("Division requires two INTS");
	}
}

Variable* modOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new int(*(int*)(var1->getValue()) % *(int*)(var2->getValue())),
			Types::INT,
			-1
		);
	} else {
		throw RuntimeException("Division requires two INTS");
	}
}

Variable* andOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::BOOLEAN && var2->getType() == Types::BOOLEAN) {
		return new Variable(
			new bool(*(bool*)(var1->getValue()) && *(bool*)(var2->getValue())),
			Types::BOOLEAN,
			-1
		);
	} else {
		throw RuntimeException("Boolean Operations require two BOOLEANS");
	}
}

Variable* orOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::BOOLEAN && var2->getType() == Types::BOOLEAN) {
		return new Variable(
			new bool(*(bool*)(var1->getValue()) || *(bool*)(var2->getValue())),
			Types::BOOLEAN,
			-1
		);
	} else {
		throw RuntimeException("Boolean Operations require two BOOLEANS");
	}
}

Variable* notOp(Variable* var1, Variable* var2) {
	if(var2->getType() == Types::BOOLEAN) {
		return new Variable(
			new bool(!(*(bool*)(var2->getValue()))),
			Types::BOOLEAN,
			-1
		);
	} else {
		throw RuntimeException("NOT Operation requires a BOOLEANS");
	}
}

Variable* ltOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new bool(*(int*)(var1->getValue()) < *(int*)(var2->getValue())),
			Types::BOOLEAN,
			-1
		);
	} else {
		throw RuntimeException("Less Than Operation requires two numeric values");
	}
}

Variable* gtOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new bool(*(int*)(var1->getValue()) > *(int*)(var2->getValue())),
			Types::BOOLEAN,
			-1
		);
	} else {
		throw RuntimeException("Greater Than Operation requires two numeric values");
	}
}

Variable* lteOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new bool(*(int*)(var1->getValue()) <= *(int*)(var2->getValue())),
			Types::BOOLEAN,
			-1
		);
	} else {
		std::cout << var1->getType() << " " << var2->getType() << std::endl;
		throw RuntimeException("Less Than or Equal To Operation requires two numeric values");
	}
}

Variable* gteOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new bool(*(int*)(var1->getValue()) >= *(int*)(var2->getValue())),
			Types::BOOLEAN,
			-1
		);
	} else {
		throw RuntimeException("Greater Than or Equal To Operation requires two numeric values");
	}
}

Variable* eqOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new bool(*(int*)(var1->getValue()) == *(int*)(var2->getValue())),
			Types::BOOLEAN,
			-1
		);
	} else {
		throw RuntimeException("Equality Operation requires two numeric values");
	}
}

Variable* neqOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::INT && var2->getType() == Types::INT) {
		return new Variable(
			new bool(*(int*)(var1->getValue()) != *(int*)(var2->getValue())),
			Types::BOOLEAN,
			-1
		);
	} else {
		throw RuntimeException("Inequality Operation requires two numeric values");
	}
}


Variable* dotOp(Variable* var1, Variable* var2) {
	if(var1->getType() == Types::OBJECT && var2->getType() == Types::LANGUAGEELEMENT) {	
		return (Variable*)(((Object*)(var1->getValue()))->getFunction(var2));
	} else if(var1->getType() == Types::FUNCTION) {
		return ((Function*)(var1))->evaluate(var2);
	} else {
		throw RuntimeException("Invalid operands for dot (.) operation (" + Types::getTypeName(var1->getType()) + " " + Types::getTypeName(var2->getType()) + ")");
	}
}


Variable* commaOp(Variable* var1, Variable* var2) {

	if(var2->getType() == Types::COMMALIST) {
		throw RuntimeException("Cannot append Comma List to Comma List");
	}

	if(var1->getType() != Types::COMMALIST) {
		return new CommaList(var1, var2);
	} else {
		((CommaList*)var1)->add(var2);
		return var1;
	}
	
}

Variable* arrayOp(Variable* var1, Variable* var2) {
	
	if(!(var2->getType() == Types::INT || var2->getType() == Types::LANGUAGEELEMENT)) {
		throw RuntimeException("Expected INT or LANGUAGEELEMENT for object initialization");
	}
	
	if(var1 == nullptr) {
		
		Object* rtn;
		if(var2->getType() == Types::INT) {
			rtn = new Array(*(int*)(var2->getValue()));
		} else if(var2->getType() == Types::LANGUAGEELEMENT) {
			std::string type = *((std::string*)(var2->getValue()));
			
			if(type.compare("stack")==0) {
				rtn = new LanguageStack();
			} else if(type.compare("queue")==0) {
				rtn = new LanguageQueue();
				
			} else if(type.compare("collection")==0) {
				rtn = new LanguageCollection();
				
			} else {
				throw new RuntimeException("Unrecognized object type \"" + type + "\"");
			}
		}
		return new Variable((void*)rtn, Types::OBJECT, -1);
	} else if(var1->getType() == Types::OBJECT) {
		if(((Object*)(var1->getValue()))->getType() == Object::ARRAY) {
			return ((Array*)(var1->getValue()))->get(*(int*)(var2->getValue()));
		} else {
			throw RuntimeException("Variable accessed with [] must be an array");
		}
	} else {
		throw RuntimeException("Variable accessed with [] must be an array");
	}
}



Operator::Operator(std::string* op, std::string* before, int idx, int dpt) {
	index = idx;
	depth = dpt;
	
	if(op->compare("-")==0) {
		if(((before == nullptr) || (Types::determineType(*before) == Types::OTHER) || (Types::determineType(*before) == Types::OPERATOR))&& (!Variable::isVariable(*before))) {
			precedence = 0;
			type = NEG;
		} else {
			precedence = 2;
			type = SUB;
		}
	} else if(op->compare(".")==0) {
		precedence = 0;
		type = DOT;
	} else if(op->compare("[")==0) {
		precedence = 0;
		type = ARRAY;
	} else if(op->compare("*")==0) {
		precedence = 1;
		type = MULT;
	} else if(op->compare("/")==0) {
		precedence = 1;
		type = DIV;
	} else if(op->compare("mod")==0) {
		precedence = 1;
		type = MOD;
	} else if(op->compare("+")==0) {
		precedence = 2;
		type = ADD;
	} else if(op->compare("<")==0) {
		precedence = 3;
		type = LT;
	} else if(op->compare(">")==0) {
		precedence = 3;
		type = GT;
	} else if(op->compare("<=")==0) {
		precedence = 3;
		type = LTE;
	} else if(op->compare(">=")==0) {
		precedence = 3;
		type = GTE;
	} else if(op->compare("==")==0) {
		precedence = 3;
		type = EQ;
	} else if(op->compare("!=")==0) {
		precedence = 3;
		type = NEQ;
	} else if(op->compare("AND")==0) {
		precedence = 4;
		type = AND;
	} else if(op->compare("OR")==0) {
		precedence = 4;
		type = OR;
	} else if(op->compare("NOT")==0) {
		precedence = 4;
		type = NOT;
	} else if(op->compare("=")==0) {
		precedence = 5;
		type = ASSIGN;
	} else if(op->compare(",")==0) {
		precedence = 6;
		type = COMMA;
	} else {
		throw RuntimeException(std::string(std::string("Unrecognized operator: ") + "\"" + *op + "\""));
	}
}

int Operator::compare(Operator& otherOp) {
	if(otherOp.depth > depth) {
		return 1;
	} else if(otherOp.depth < depth) {
		return -1;
	} else {
		if(otherOp.precedence < precedence) {
			return 1;
		} else
			return -1;
	}
	
}


Variable* Operator::evaluate(Variable* var1, Variable* var2) {
	switch(type) {
		case ASSIGN:
			return assignOp(var1, var2);
		case ADD:
			return addOp(var1, var2);
		case SUB: 
			return subOp(var1, var2);
		case MULT: 
			return multOp(var1, var2);
		case DIV: 
			return divOp(var1, var2);
		case MOD:
			return modOp(var1, var2);
		case NEG:
			return negOp(var1, var2);
		case AND:
			return andOp(var1, var2);
		case OR: 
			return orOp(var1, var2);
		case NOT:
			return notOp(var1, var2);
		case LT: 
			return ltOp(var1, var2);
		case GT: 
			return gtOp(var1, var2);
		case LTE: 
			return lteOp(var1, var2);
		case GTE: 
			return gteOp(var1, var2);
		case NEQ: 
			return neqOp(var1, var2);
		case EQ:
			return eqOp(var1, var2);
		case DOT: 
			return dotOp(var1, var2);
		case COMMA:
			return commaOp(var1, var2);
		case ARRAY:
			return arrayOp(var1, var2);
	}
}


void Operator::printDetails() {
	std::cout << "Index: " << index << " Precedence: " << precedence << " Depth: " << depth << " Type: ";
	print();
	std::cout << " | ";
}

void Operator::print() {
	switch(type) {
		case ASSIGN:
			std::cout << "="; break;
		case ADD:
			std::cout << "+"; break;
		case SUB: 
			std::cout << "-"; break;
		case MULT: 
			std::cout << "*"; break;
		case DIV: 
			std::cout << "/"; break;
		case MOD:
			std::cout << "mod"; break;
		case NEG:
			std::cout << "NEG"; break;
		case AND:
			std::cout << "AND"; break;
		case OR: 
			std::cout << "OR"; break;
		case NOT:
			std::cout << "NOT"; break;
		case LT: 
			std::cout << "<"; break;
		case GT: 
			std::cout << ">"; break;
		case LTE: 
			std::cout << "<="; break;
		case GTE: 
			std::cout << ">="; break;
		case NEQ: 
			std::cout << "!="; break;
		case EQ:
			std::cout << "=="; break;
		case DOT: 
			std::cout << "."; break;
		case COMMA:
			std::cout << ","; break;
		case ARRAY:
			std::cout << "["; break;
			
	}
}

const std::regex Operator::operatorRegex = std::regex("[^a-zA-Z\\d\\s]+");

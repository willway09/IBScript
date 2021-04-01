#ifndef _LANGUAGEQUEUE_HPP
#define _LANGUAGEQUEUE_HPP

#include "DataStructures/Queue.hpp"
#include "Object.hpp"

class LanguageQueue : public Object {
	private:
		Queue<Variable> variableQueue;
		Types::TypeName queueType = Types::OTHER;
		
	public:
		LanguageQueue() : Object(Object::QUEUE) { }
		
		void deleteObject();
		Function* getFunction(Variable* var);
		Variable* evaluateFunction(std::string& functionName, Variable* parameters);
};

#endif //_LANGUAGEQUEUE_HPP
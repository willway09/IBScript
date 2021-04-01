#include "VariableHashMap.hpp"

void VariableHashMap::removeWithScope(int s) {
	
	for(int i = 0; i < size; i++) {
		if(internalArray[i] != nullptr) {
			HashMapNode<VariableName, Variable>* base = new HashMapNode<VariableName, Variable>();
			base->setNext(internalArray[i]);
			
			HashMapNode<VariableName, Variable>* node = base;
			
			while(node->getNext() != nullptr) {
				if(node->getNext()->getValue()->getScope() == s) {
					node->removeNext();
					contentsCount--;
				} else {
					node = node->getNext();
				}
			}

			internalArray[i] = base->getNext();
						
			base->setNext(nullptr);
			delete base;
		}
	}
}

void VariableHashMap::printVariables() {
	for(int i = 0; i < size; i++) {
		HashMapNode<VariableName, Variable>* node = internalArray[i];
		
		while(node != nullptr) {
			
			node->getValue()->print();
			std::cout << " | ";
			
			node = node->getNext();
		}
		std::cout << std::endl;
	}
}
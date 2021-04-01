#ifndef _LISTITERATOR_HPP
#define _LISTITERATOR_HPP

#include "Node.hpp"
#include "ListIteratorException.hpp"

template <typename T> class ListIterator {
	private:
		Node<T>* workingNode;
		
	public:
		ListIterator(Node<T>* node) : workingNode(node) { }
		
		void setValue(T* t) throw(ListIteratorException) {
			if(workingNode != nullptr)
				workingNode->setInfo(t);
			else
				throw ListIteratorException();
		}
		
		T* getValue() throw(ListIteratorException) {
			if(workingNode != nullptr)
				return workingNode->getT();
			else
				throw ListIteratorException();
		}
		
		void next() throw(ListIteratorException) {
			if(workingNode != nullptr) {
				workingNode = workingNode->getNext();
			} else {
				throw ListIteratorException();
			}
		}
		
		bool hasMore() {
			return (workingNode != nullptr ? true : false);
		}
		
};

#endif //_LISTITERATOR_HPP
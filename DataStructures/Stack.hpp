#ifndef _STACK_HPP
#define _STACK_HPP
#include "SinglyLinkedList.hpp"

template <typename T> class Stack : SinglyLinkedList<T> {
	private:
	
	public:
	
		Stack() : SinglyLinkedList<T>::SinglyLinkedList() { }
	
		int size() { return SinglyLinkedList<T>::size(); }
		bool isEmpty() { if(size() == 0) return true; else return false; }
		bool isFull() { return false; } //Implemented using a linked list, so technically not appropriate
		
		void push(T*) throw (ListException);
		T* pop() throw (ListException);
		T* top() throw (ListException);
		
};

#include "Stack.tpp"

#endif //_STACK_HPP
#ifndef _QUEUE_HPP
#define _QUEUE_HPP

#include "SinglyLinkedList.hpp"

template <typename T> class Queue : SinglyLinkedList<T> {
	protected:
		void sort();
	public:
		Queue() : SinglyLinkedList<T>::SinglyLinkedList() { }
		
		int size() { return SinglyLinkedList<T>::size(); }
		bool isEmpty() { if(size() == 0) return true; else return false; }
		bool isFull() { return false; } //Implemented using a linked list, so technically not appropriate
		
		void enqueue(T* t) throw(ListException);
		T* dequeue() throw(ListException);
		T* front() throw(ListException);
		T* rear() throw(ListException);
		
};


#include "Queue.tpp"

#endif //_QUEUE_HPP
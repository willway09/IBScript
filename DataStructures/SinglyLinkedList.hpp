#ifndef _SINGLYLINKEDLIST_HPP
#define _SINGLYLINKEDLIST_HPP

#include "Node.hpp"
#include "ListException.hpp"
#include "ListIterator.hpp"
#include <iostream>

template <typename T> class SinglyLinkedList {
  private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr; //Tail pointer added to improve end-of-list access speed
    int listSize = 0;

    void deleteNodesRecursively(Node<T>* n);
	Node<T>* getNode(int index) throw(ListException);
	void print(Node<T>* n);
	bool contains(T*);
	
	void checkContains(T* info) throw(ListException) { //Should be inline
		if(contains(info)) {
			ListException e(ListException::DUPLICATE, listSize);
			throw e;
		}
	}
	
	void checkIndexAdd(int index) throw(ListException) { //Should be inline
		if(index < 0 || index > listSize) {
			ListException e(ListException::OUT_OF_BOUNDS, listSize, index);
			throw e;
		}
	}
	
	void checkIndexAccess(int index) throw(ListException) {
		if(index < 0 || index >= listSize) {
			ListException e(ListException::OUT_OF_BOUNDS, listSize, index);
			throw e;
		}
	}
	
	Node<T>* mergeSortRecursive(Node<T>* base, int size);
	//void printForMerge(Node<T>* n);

  public:
    SinglyLinkedList();
    SinglyLinkedList(T* headT);

    ~SinglyLinkedList();

    //Useful methods
    int size() { return listSize; }
	bool isEmpty();
	bool isFull();

    T* getFirst() throw(ListException);
    T* getLast() throw(ListException);


    void clear();
	void clearWithoutDeletingContents();

    void insertHead(T* info) throw(ListException);
    void insertTail(T* info) throw(ListException);

    void add(T* info) throw(ListException);

    void insertAfter(int index, T* info) throw(ListException);
	void insertAt(int index, T* info) throw(ListException);
	
	void removeHead() throw(ListException);
	void removeTail() throw(ListException);
	
	void removeLast() throw(ListException);
	
	void removeAfter(int index) throw(ListException);
	void removeAt(int index) throw(ListException);
	
	T* extractAfter(int index) throw(ListException);
	T* extractAt(int index) throw(ListException);
	
	void mergeSort();
	
	
	T* get(int index) throw(ListException);
		
	void extractToArray(T** array);
	
	void print();
	void printStatistics();

	
	ListIterator<T>* getIterator();

};

#include "SinglyLinkedList.tpp"

#endif //_SINGLYLINKEDLIST_HPP

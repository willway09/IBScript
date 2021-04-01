#include "SinglyLinkedList.hpp"
#include <iostream>

template <typename T> void SinglyLinkedList<T>::deleteNodesRecursively(Node<T>* n) {
  if(n->getNext() == nullptr) {
    delete n;
    return;
  }
  deleteNodesRecursively(n->getNext());
}

template <typename T> SinglyLinkedList<T>::SinglyLinkedList() {	
  //Technically don't need to do anything, as all setup is just initialization
  //to nullptr and 0. Still, user should have ability to make an empty list for
  //later use
}

template <typename T> SinglyLinkedList<T>::SinglyLinkedList(T* headT) {
  add(headT);
}

template <typename T> SinglyLinkedList<T>::~SinglyLinkedList() {
	clear();
}

template <typename T> T* SinglyLinkedList<T>::getFirst() throw(ListException) {
	checkIndexAccess(0);
	return head->getT();
}

template <typename T> T* SinglyLinkedList<T>::getLast() throw(ListException) {
	checkIndexAccess(listSize - 1);
	return tail->getT();
}

template <typename T> bool SinglyLinkedList<T>::isEmpty() {
    if(listSize == 0) return true;
    else return false;
}

template <typename T> bool SinglyLinkedList<T>::isFull() {
	return !isEmpty();
}


template <typename T> void SinglyLinkedList<T>::clear() {
	if(head != nullptr)
		deleteNodesRecursively(head);
  head = nullptr;
  tail = nullptr;
  listSize = 0;
}

template <typename T> void SinglyLinkedList<T>::clearWithoutDeletingContents() {
		
	Node<T>* temp = nullptr;
	
	while(head != nullptr) {
		head->setNext(nullptr);
		temp = head->getNext();
		head->setNext(nullptr);
		delete head;
		head = temp;
	}
		
	
	
	head = nullptr;
	tail = nullptr;
	listSize = 0;
}

template <typename T> void SinglyLinkedList<T>::insertHead(T *info) throw(ListException) {
	
	checkContains(info);
	
  head = new Node<T>(info, head, Node<T>::BEFORE_HEAD);
  
  if(listSize == 0) tail = head;
  listSize++;
  
}
template <typename T> void SinglyLinkedList<T>::insertTail(T* info) throw(ListException) {
    add(info); //Just call add, does same thing, method included for completeness
}

template <typename T> void SinglyLinkedList<T>::add(T* info) throw(ListException) {
	checkContains(info);
	
  tail = new Node<T>(info, tail);

  if(listSize == 0) head = tail; //Set head pointer if no other elements

  listSize++;
}

template <typename T> void SinglyLinkedList<T>::insertAfter(int index, T* info) throw(ListException) {
	
	insertAt(index + 1, info);
	
}

template <typename T> void SinglyLinkedList<T>::insertAt(int index, T* info) throw(ListException) {
	
	checkContains(info);
	checkIndexAdd(index);
	
	if(index == listSize) {
		insertTail(info);
	} else if(index == 0) {
		insertHead(info);
	} else {
		Node<T>* n = getNode(index - 1);
		new Node<T>(info, n);
		listSize++;
	}
}

template <typename T> Node<T>* SinglyLinkedList<T>::getNode(int index) throw(ListException) {
	
	checkIndexAccess(index);
	
	//if(head == nullptr) return nullptr;
	
	Node<T>* p = head;
	
	for(int i = 0; i < index; i++) {
		p = p->getNext();
		//if(p == nullptr) return nullptr;
	}
	
	return p;
}

template <typename T> void SinglyLinkedList<T>::removeHead() throw(ListException) {
	Node<T>* temp = head;
	head = head->getNext();
	
	if(listSize == 1) tail = nullptr;
	
	delete temp;
	listSize--;
}

template <typename T> void SinglyLinkedList<T>::removeTail() throw(ListException) { //Included for completeness, just calls removeLast()
	removeLast();
}

template <typename T> void SinglyLinkedList<T>::removeLast() throw(ListException) {
	if(listSize == 1) {
		removeHead();
	} else {
		tail = getNode(listSize - 2);
		delete (tail->getNext());
		tail->setNext(nullptr);
		listSize--;
	}
}

template <typename T> void SinglyLinkedList<T>::removeAfter(int index) throw(ListException) {
	removeAt(index + 1);
}

template <typename T> void SinglyLinkedList<T>::removeAt(int index) throw(ListException) {
	if(index == listSize - 1) {
		removeTail();
	} else if(index == 0) {
		removeHead();
	} else {
		Node<T>* temp = getNode(index - 1);
		Node<T>* toDelete = temp->getNext();
		temp->setNext(toDelete->getNext());
		delete toDelete;
		listSize--;
	}
}

template <typename T> T* SinglyLinkedList<T>::extractAfter(int index) throw(ListException) {
	return extractAt(index + 1);
}

template <typename T> T* SinglyLinkedList<T>::extractAt(int index) throw(ListException) {
	Node<T>* temp = getNode(index);
	T* rtn = temp->getT();
	temp->setInfo(nullptr);
	removeAt(index);
	return rtn;
}


template <typename T> T* SinglyLinkedList<T>::get(int index) throw(ListException) {
	return getNode(index)->getT();
}

template <typename T> bool SinglyLinkedList<T>::contains(T* info) {
	if(head == nullptr) return false;
	
	Node<T>* p = head;
	
	if(p->getT() == info) return true;
	
	while(p->getNext() != nullptr) {
		p = p->getNext();
		if(p == nullptr) std::cout << "Big error" << std::endl;
		if(p->getT() == info) return true;
	}
	
	return false;
}

template <typename T> Node<T>* SinglyLinkedList<T>::mergeSortRecursive(Node<T>* base, int size) {	
	if(size == 1) {
		//std::cout << *(base->getT()) << std::endl;
		base->setNext(nullptr);
		return base;
	}
	
	int midIdx = (size / 2);
	Node<T>* midNode = base;
	
	int aSize = midIdx;
	int bSize = size - aSize;
	
	for(int i = 0; i < midIdx; i++) {
		midNode = midNode->getNext();
	}
	
	/*std::cout << *(base->getT()) << std::endl;
	std::cout << *(midNode->getT()) << std::endl;
	std::cout << "aSize: " << aSize << " | bSize: " << bSize << std::endl;*/
	
	Node<T>* a = mergeSortRecursive(base, aSize);
	Node<T>* b = mergeSortRecursive(midNode, bSize);
	
	Node<T>* rtn = nullptr;
	Node<T>* end = nullptr;
	
	//Got to start it off
	if(a->getT()->compare(*(b->getT())) >= 0) {
		rtn = a;
		a = a->getNext();
	} else {
		rtn = b;
		b = b->getNext();
	}
	
	end = rtn;
	
	
	//Then loop through
	while(a != nullptr || b!= nullptr) {
		
		//std::cout << *(a->getT()) << " " << *(b->getT()) << std::endl;
		
		if(a == nullptr) {
			//std::cout << "A " << *(b->getT()) << std::endl;
			end->setNext(b);
			break;
		} else if(b == nullptr) {
			//std::cout << "B " << *(a->getT()) << std::endl;
			end->setNext(a);
			break;
		} else {
			//std::cout << "C ";
			if(a->getT()->compare(*(b->getT())) >= 0) {
				//std::cout << "1" << std::endl;
				end->setNext(a);
				end = end->getNext();
				a = a->getNext();
			} else {
				//std::cout << "2" << std::endl;
				end->setNext(b);
				end = end->getNext();
				b = b->getNext();				
			}
		
		}
		
	}
	
	return rtn;
	
}

template <typename T> void SinglyLinkedList<T>::mergeSort() {
	head = mergeSortRecursive(head, listSize);
	tail = getNode(listSize - 1);
}


template <typename T> void SinglyLinkedList<T>::print(Node<T>* n) {
	std::cout << *(n->getT()) << std::endl;;
	if(n->getNext() != nullptr) print(n->getNext());
}

template <typename T> void SinglyLinkedList<T>::extractToArray(T** array) {
	Node<T>* node = head;
	
	int i = 0;
	while(node != nullptr) {
		array[i] = node->getT();
		node->setInfo(nullptr);
		node = node->getNext();
		i++;
	}
}

template <typename T> void SinglyLinkedList<T>::print() {
	if(head != nullptr) print(head);
	printStatistics();
}

template <typename T> void SinglyLinkedList<T>::printStatistics() {
	std::cout << "Head: ";
	if(head == nullptr) {
		std::cout << "nullptr";
	} else {
		std::cout << (void*)head;
	}
	std::cout << std::endl;
	
	std::cout << "Tail: ";
	if(tail == nullptr) {
		std::cout << "nullptr";
	} else {
		std::cout << (void*)tail;
	}
	std::cout << std::endl;
	
	std::cout << "List size: " << listSize << std::endl;
	std::cout << "======================================" << std::endl;
}

template <typename T> ListIterator<T>* SinglyLinkedList<T>::getIterator() {
	return new ListIterator<T>(head);
}
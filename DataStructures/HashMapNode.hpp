#ifndef _HASHMAPNODE_HPP
#define _HASHMAPNODE_HPP
#include <iostream>

template <class K, class T> class HashMapNode {
	private:
		K* key;
		T* info;
		HashMapNode<K, T>* next = nullptr;
		
	public:
		HashMapNode();
		HashMapNode(K* k, T* t);
	
		~HashMapNode();
	
		HashMapNode<K, T>* getNext() { return next; };
		void setNext(HashMapNode<K, T>* t) { next = t; };
		//void setNext(HashMapNode<T>* t);
		void removeNext();
		
		void addToEnd(K* k, T* t);
		//void insertAfter();
		
		T* getValue() { return info; }
		K* getKey() { return key; }
		
		void clear();
};

#include "HashMapNode.tpp"

#endif //_HASHMAPNODE_HPP
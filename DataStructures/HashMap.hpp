#ifndef _HASHMAP_HPP
#define _HASHMAP_HPP
#include "HashMapNode.hpp"
#include <iostream>

template<typename K, typename T> class HashMap {
	protected:
		HashMapNode<K, T>** internalArray;
		
		int cellFillCount = 0;
		int contentsCount = 0;
		int size = 0;
		
		float loadFactor = .75f;
		float increaseFactor = 2.0f;
		
	public:
		HashMap();
		HashMap(int s);
		~HashMap();
		
		void add(K* k, T* t);
		T* get(K* k);
		
		bool containsKey(K* t);
		bool containsValue(T* t);
		
		void resizeHashMap();
		
		int getCellFillCount() { return cellFillCount; }
		int getContentsCount() { return contentsCount; }
		int getSize() { return size; }
		
		void status();
		
		
};
#include "HashMap.tpp"

#endif //_HASHMAP_HPP
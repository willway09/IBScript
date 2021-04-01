/*std::string isNullPointer(void* v) {
	if(v == nullptr) {
		return "is a Null Pointer";
	} else {
		return "is NOT a Null Pointer";
	}
}*/

template<typename K, typename T> HashMap<K, T>::HashMap() : HashMap(10) {
}

template<typename K, typename T> HashMap<K, T>::HashMap(int s) {
	size = s;
	internalArray = new HashMapNode<K, T>*[size];
	
	for(int i = 0; i < size; i++) {
		internalArray[i] = nullptr;
	}
	
	contentsCount = 0;
	cellFillCount = 0;
}

template<typename K, typename T> HashMap<K, T>::~HashMap() {
	for(int i = 0; i < size; i++) {
		if(internalArray[i] != nullptr) {
			delete internalArray[i];
		}
	}
}

template<typename K, typename T> void HashMap<K, T>::add(K* k, T* t) {
	
	if((contentsCount + 1) / (1.0f * size) > loadFactor) {
		resizeHashMap();
	}
	
	int hash = k->hashCode() % size;
	hash = (hash >= 0 ? hash : -hash);
	
	HashMapNode<K, T>* node = internalArray[hash];
	
	if(node == nullptr) {
		internalArray[hash] = new HashMapNode<K, T>(k, t);
		cellFillCount++;
	} else {
		node->addToEnd(k, t);
	}

	contentsCount++;
}

template<typename K, typename T> T* HashMap<K, T>::get(K* k) {
	
	int hash = k->hashCode() % size;
	hash = (hash >= 0 ? hash : -hash);
	
	HashMapNode<K,T>* node = internalArray[hash];

	
	if(node == nullptr) {
		return nullptr;
	} else {
		while(node != nullptr) {
			if(node->getKey()->equals(k)) {
				return node->getValue();
			}
			node = node->getNext();
		}
	}
	return nullptr;
}

template<typename K, typename T> bool HashMap<K, T>::containsKey(K* k) {
	int hash = k->hashCode() % size;
	hash = (hash >= 0 ? hash : -hash);
	
	HashMapNode<K,T>* node = internalArray[hash];
	
	if(node == nullptr) {
		return false;
	} else {
		while(node != nullptr) {
			if(node->getKey()->equals(k)) {
				return true;
			}
			node = node->getNext();
		}
	}
	return false;

}

template<typename K, typename T> void HashMap<K, T>::status() {
	for(int i = 0; i < size; i++) {
		
		HashMapNode<K, T>* node = internalArray[i];
		
		std::cout << (void*)node << ", ";
		
		if(node != nullptr) {
			std::cout << *(node->getKey()) << ", " << (node->getValue());
		}
		std::cout << "; ";
		
		if(node != nullptr) {
			while(node->getNext() != nullptr) {
				node = node->getNext();
				std::cout << (void*)node << ", " << *(node->getKey()) << ", " << (node->getValue()) << "; ";
			}
		}
		
		std::cout << std::endl;
	}
}

template<typename K, typename T> void HashMap<K, T>::resizeHashMap() {
	int oldSize = size;
	
	size = (int)(oldSize * increaseFactor);
	
	HashMapNode<K, T>** oldArray = internalArray;
	internalArray = new HashMapNode<K, T>*[size];
	
	for(int i = 0; i < size; i++) {
		internalArray[i] = nullptr;
	}

	
	contentsCount = 0;
	cellFillCount = 0;

	
	for(int i = 0; i < oldSize; i++) {
		if(oldArray[i] != nullptr) {
			HashMapNode<K, T>* node = oldArray[i];
			
			while(node != nullptr) {
				add(node->getKey(), node->getValue());
				node->clear();
				node = node->getNext();
			}
			
			delete oldArray[i];
		}
	}
	
	delete oldArray;
}

/*template<typename K, typename T> bool HashMap<K, T>::containsValue(T* t) {
	
}*/
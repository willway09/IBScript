template <typename K, typename T> HashMapNode<K, T>::HashMapNode() {
	key = nullptr;
	info = nullptr;
	next = nullptr;
}

template <typename K, typename T> HashMapNode<K, T>::HashMapNode(K* k, T* t) {
	key = k;
	info = t;
	next = nullptr;
}

template <typename K, typename T> HashMapNode<K, T>::~HashMapNode() {
	delete info;
	delete key;
	if(next != nullptr) {
		delete next;
	}
}

template<typename K, typename T> void HashMapNode<K, T>::removeNext() {
	if(next != nullptr) {
		HashMapNode<K, T>* temp = next;
		next = next->getNext();
		temp->setNext(nullptr);
		delete temp;
	}
}

template<typename K, typename T> void HashMapNode<K, T>::addToEnd(K* k, T* t) {
	if(next == nullptr) {
		next = new HashMapNode<K, T>(k, t);
	} else {
		next->addToEnd(k, t);
	}
}

template<typename K, typename T> void HashMapNode<K, T>::clear() {
	key = nullptr;
	info = nullptr;
}
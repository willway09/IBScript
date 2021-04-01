template <typename T> void Stack<T>::push(T* t) throw(ListException){
	SinglyLinkedList<T>::insertHead(t);
}


//NOTE: All popped values MUST be deleted by the user
template <typename T> T* Stack<T>::pop() throw(ListException) {
	return SinglyLinkedList<T>::extractAt(0);
}

//NOTE: All values obtained from top must NOT be deleted by the user
template <typename T> T* Stack<T>::top() throw(ListException) {
	return SinglyLinkedList<T>::getFirst();
}
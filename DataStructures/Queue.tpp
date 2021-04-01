template <typename T> void Queue<T>::enqueue(T* t) throw(ListException) {
	SinglyLinkedList<T>::insertTail(t);
}
template <typename T> T* Queue<T>::dequeue() throw(ListException) {
	return SinglyLinkedList<T>::extractAt(0);
}
template <typename T> T* Queue<T>::front() throw(ListException) {
	return SinglyLinkedList<T>::getFirst();
}
template <typename T> T* Queue<T>::rear() throw(ListException) {
	return SinglyLinkedList<T>::getLast();
}

template <typename T> void Queue<T>::sort() {
	SinglyLinkedList<T>::mergeSort();
}
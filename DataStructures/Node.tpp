#include "Node.hpp"

template <typename T> Node<T>::Node(T* i) {
  info = i;
}

template <typename T> Node<T>::Node(T* i, Node<T>* n, position pos) : Node(i) {

  if(pos == AFTER) {

    if(n != nullptr) {
      next = n->getNext();
      n->setNext(this);
    }
  } else if(pos == BEFORE_HEAD) {
    next = n;
  }

}


template <typename T> Node<T>::~Node() {
  delete info;
}

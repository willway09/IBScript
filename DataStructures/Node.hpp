#ifndef _NODE_HPP
#define _NODE_HPP

#include "Info.hpp"

template <typename T> class Node {
  private:
    Node<T>* next = nullptr;

    T* info = nullptr;

  public:
  
	enum position { AFTER = 0, BEFORE_HEAD};
  
    Node<T>* getNext() { return next; };
    void setNext(Node<T>* n) { next = n; };

    T* getT() { return info; };
    void setInfo(T* i) { info = i; };
	


    /*///////////////

    NOTE: ALL DATA ADDED USING TO LIST SHOULD NOT BE DELETED BY USER
    DATA DELETEION IS MANAGED BY THE NODE/LIST IMPLEMENTATION

    *///////////////////
    //New constructor
    Node(T* i);
    //Insert after or before constructor
    Node(T* i, Node<T>* n, position pos = AFTER);



    ~Node();

};
#include "Node.tpp"

#endif //_NODE_HPP

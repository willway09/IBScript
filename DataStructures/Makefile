all : SinglyLinkedList.o
	g++ -std=c++11 -o Main.exe Main.cpp Info.o ListException.o #SinglyLinkedList.o Node.o Info.o

clean :
	rm *.o

SinglyLinkedList.o : SinglyLinkedList.tpp SinglyLinkedList.hpp Node.o ListException.o
	g++ -std=c++11 -c -o SinglyLinkedList.o SinglyLinkedList.hpp
	
Node.o : Node.tpp Node.hpp Info.o
	g++ -std=c++11 -c -o Node.o Node.hpp
	
Info.o : Info.cpp Info.hpp
	g++ -std=c++11 -c -o Info.o Info.cpp
	
ListException.o : ListException.cpp ListException.hpp
	g++ -std=c++11 -c -o ListException.o ListException.cpp
	
Stack.o : Stack.hpp SinglyLinkedList.o
	g++ -std=c++11 -c -o Stack.o Stack.hpp
	
Queue.o : Queue.hpp SinglyLinkedList.o
	g++ -std=c++11 -c -o Queue.o Queue.hpp
	
HahsMap.o : HashMap.hpp HashMap.tpp HashMapNode.o
	g++ -std=c++11 -c -o HashMap.o HashMap.hpp
	
HashMapNode.o : HashMapNode.hpp HashMapNode.tpp
	g++ -std=c++11 -c -o HashMapNode.o HashMapNode.hpp
	
#include "SinglyLinkedList.hpp"
#include <string>

int main() {
	
	/*try {
		SinglyLinkedList <Info> list;
		
		list.printStatistics();
		
		list.add(new Info("Will", 18, 15.4));
		list.print();

		list.insertHead(new Info("John", 23,52));
		list.print();
		
		list.insertAt(1, new Info("Rithvi", 42,53));
		list.print();
		
		list.removeAt(1);
		list.print();
		
		list.removeAt(0);
		list.print();
		
		list.removeAt(0);
		list.print();
		
		Info* george = new Info("George", 5,5);
		
		list.add(george);
		list.print();

		list.insertAt(1, new Info("Ben", -1, -1));
		list.print();
		
		std::cout << "Got Here" << std::endl;
		
		list.add(george);
		list.print();
		
		
		
	} catch(ListException& e) {
		//std::cout << e.what() << std::endl;
	}*/
	
	SinglyLinkedList<std::string> list;
	
	list.add(new std::string("4"));
	list.add(new std::string("3"));
	list.add(new std::string("8"));
	list.add(new std::string("7"));
	list.add(new std::string("2"));
	list.add(new std::string("5"));
	list.add(new std::string("1"));
	//list.add(new std::string("6"));
	
	list.mergeSort();
	
	std::cout << "================" << std::endl;
	
	list.print();
}
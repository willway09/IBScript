#include <iostream>

#include "TestException.hpp"

void sayHello(int a) throw(TestException) {
	
	if(a == 0) {
		TestException e;
		e.a = 59;
		throw e;
		std::cout << "Exception thrown" << std::endl;
	}
	std::cout << "Hello World" << std::endl;
}

int main(int argc, char** argv) {

	sayHello(1);
	sayHello(2);
	//sayHello(0);

	
	try {
		sayHello(0);
	} catch(TestException& e) {
		std::cout << "Error caught: " << e.a << std::endl;
	}
	
}
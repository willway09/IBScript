#include <iostream>
#include <string>

#include "Stack.hpp"
#include "Queue.hpp"

int main() {
	Queue<int> queue;
	
	for(int i = 0; i < 50; i++) {
		queue.enqueue(new int(i));
	}
	
	while(queue.size() > 0) {
		int* temp = queue.dequeue();
		std::cout << *temp << std::endl;
		delete temp;
	}	
	
}
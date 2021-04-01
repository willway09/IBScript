#ifndef _PRIORITYQUEUE_HPP
#define _PRIORITYQUEUE_HPP

#include "Queue.hpp"

template <typename T> class PriorityQueue : public Queue<T> {
	public:
		void prioritize() {
			Queue<T>::sort();
		}
};

#endif //_PRIORITYQUEUE_HPP
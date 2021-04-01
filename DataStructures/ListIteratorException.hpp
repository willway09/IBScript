#ifndef _LISTITERATOREXCEPTION_HPP
#define _LISTITERATOREXCEPTION_HPP

class ListIteratorException : public std::exception {	
	public:
		virtual const char* what() {
			return "Accessing out-of-bounds element of list";
		}
};

#endif //_LISTITERATOREXCEPTION_HPP
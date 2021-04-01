#ifndef _LIST_EXCEPTION
#define _LIST_EXCEPTION

#include <exception>
#include <string>

class ListException : public std::exception {
	public:
		enum ExceptionType {OUT_OF_BOUNDS = 0, DUPLICATE};
	private:
		ExceptionType type;
		
		int listLength;
		int index;
		
		std::string* returnString;
	public:
		
		int getIndex() { return index; }
		int getListLength() { return listLength; }
		ExceptionType getType() { return type; }
		
		virtual const char* what() const throw();
		
		ListException(ExceptionType tp, int length, int idx = -1);
		~ListException();
};

#endif //_LIST_EXCEPTION
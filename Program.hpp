#ifndef _PROGRAM_HPP
#define _PROGRAM_HPP

#include "Parser.hpp"
#include "Segment.hpp"

class Program : public Segment {
	public:
		Program(std::string* lines, int lineCount);
		~Program();
		
		void execute();
		void print();
		void printSimple() { }
};

#endif //_PROGRAM_HPP
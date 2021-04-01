#ifndef _CONTROLSTRUCTUREMOD_HPP
#define _CONTROLSTRUCTUREMOD_HPP

#include "Line.hpp"
#include <iostream>
#include "RuntimeException.hpp"

class ControlStructureMod : public Line {
	public:
		enum ModType {
			LOOP, CONDITIONAL, ELSE
		};
		
	private:
		ModType modType;
		
	public:
		ControlStructureMod(std::string line, VariableHashMap& vars, int scope) : Line(line, vars, scope) {
			
						
			//std::cout << "ControlStructureMod line" << std::endl;
			
			//std::cout << "ControlStructureMod constructor: " << line << std::endl;
			
			type = Statement::CONTROLSTRUCTUREMOD;
			
			if(line.compare("loop")==0) {
				modType = LOOP;
			} else if(line.compare("if")==0) {
				modType = CONDITIONAL;
			} else if(line.compare("else")==0) {
				modType = ELSE;
			} else {
				throw RuntimeException("Unexpected token \"" + line + "\" in control structure");
			}
			
			
		}
		
		ModType getModType() {
			return modType;
		}
};

#endif //_CONTROLSTRUCTUREMOD_HPP
#ifndef _TYPES_HPP
#define _TYPES_HPP

#include <string>
#include <regex>

class Types {
	private:
		static const std::regex stringRegex;
		static const std::regex intRegex;
		static const std::regex languageElementRegex;
	
	public:
	
		enum TypeName {
			OTHER, VARIABLE, OPERATOR, INT, DOUBLE, BOOLEAN, STRING, COMMALIST, OBJECT, LANGUAGEELEMENT, FUNCTION
		};
		
		static std::string getTypeName(TypeName t) {
			
			if(t == INT) {
				return "INT";
			} else if( t == DOUBLE) {
				return "DOUBLE";
			} else if( t == BOOLEAN) {
				return "BOOLEAN";
			} else if( t == STRING) {
				return "STRING";
			} else if( t == COMMALIST) {
				return "COMMALIST";
			} else if( t == OBJECT) {
				return "OBJECT";
			} else if( t == OTHER) {
				return "OTHER";
			} else if(t == LANGUAGEELEMENT) {
				return "LANGUAGEELEMENT";
			} else {
				return "TYPE UNKNOWN";
			}
		}
		
		static TypeName determineType(std::string& token) {
			
			if(&token==nullptr) return OTHER;
			
			if(std::regex_match(token, stringRegex)) {
				return STRING;
			} else if(std::regex_match(token, intRegex)) {
				return INT;
			} else if(token.compare("true")==0 || token.compare("false")==0) {
				return BOOLEAN;
			} else if(isLanguageElement(token)) {
				return LANGUAGEELEMENT;
			} else {
				return OTHER;
			}
		}
		
				
		static bool isLanguageElement(std::string& s) {
			
			if(s.compare("true")==0 || s.compare("false")==0 || s.compare("if") == 0 || s.compare("else")==0 || s.compare("then")==0 || s.compare("loop")==0 || s.compare("end")==0 || s.compare("output")==0 || s.compare("to")==0 || s.compare("from")==0) return false;
			return std::regex_match(s, languageElementRegex);
		}
};

#endif //_TYPES_HPP
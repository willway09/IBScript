all : Interpreter.cpp Tokenizer.o VariableHashMap.o Operator.o ProgramStructure Types.o Array.o CommaList.o Line.o ArrayVariable.o LanguageStack.o LanguageQueue.o LanguageCollection.o Function.o ide
	g++ -std=c++11 -o ibscript.exe Interpreter.cpp Parser.o Conditional.o Loop.o ControlStructure.o Program.o ForLine.o Line.o VariableHashMap.o LanguageQueue.o LanguageStack.o LanguageCollection.o Array.o Function.o ArrayVariable.o CommaList.o Variable.o Tokenizer.o VariableName.o Operator.o Types.o DataStructures/ListException.o
	cp IBScript.jar ibscript.exe build

Tokenizer.o : Tokenizer.hpp Tokenizer.cpp
	g++ -std=c++11 -c -o Tokenizer.o Tokenizer.cpp
	
Variable.o : Variable.hpp Variable.cpp Types.o
	g++ -std=c++11 -c -o Variable.o Variable.cpp
	
CommaList.o : CommaList.hpp CommaList.cpp
	g++ -std=c++11 -c -o CommaList.o CommaList.cpp
	
ArrayVariable.o : ArrayVariable.hpp ArrayVariable.cpp
	g++ -std=c++11 -c -o ArrayVariable.o ArrayVariable.cpp

Array.o : Array.hpp Array.cpp Object.hpp
	g++ -std=c++11 -c -o Array.o Array.cpp
	
LanguageCollection.o : LanguageCollection.hpp LanguageCollection.cpp Object.hpp
	g++ -std=c++11 -c -o LanguageCollection.o LanguageCollection.cpp
	
LanguageStack.o : LanguageStack.hpp LanguageStack.cpp Object.hpp
	g++ -std=c++11 -c -o LanguageStack.o LanguageStack.cpp
	
LanguageQueue.o : LanguageQueue.hpp LanguageQueue.cpp Object.hpp
	g++ -std=c++11 -c -o LanguageQueue.o LanguageQueue.cpp
	
VariableName.o : VariableName.hpp VariableName.cpp
	g++ -std=c++11 -c -o VariableName.o VariableName.cpp
	
VariableHashMap.o : VariableHashMap.hpp VariableHashMap.cpp DataStructures/HashMap.hpp DataStructures/HashMap.tpp
	g++ -std=c++11 -c -o VariableHashMap.o VariableHashMap.cpp
	
Types.o : Types.hpp Types.cpp
	g++ -std=c++11 -c -o Types.o Types.cpp
	
Operator.o : Operator.hpp Operator.cpp
	g++ -std=c++11 -c -o Operator.o Operator.cpp

Function.o : Function.hpp Function.cpp
	g++ -std=c++11 -c -o Function.o Function.cpp

	
ProgramStructure : Parser.o Variable.o VariableName.o VariableHashMap.o Line.o Loop.o Conditional.o Program.o ForLine.o ControlStructure.o
#	g++ -std=c++11 -o a.exe StructureTestbed.cpp Parser.o Conditional.o Loop.o ControlStructure.o Program.o ForLine.o Line.o Variable.o VariableName.o VariableHashMap.o Operator.o Types.o DataStructures/ListException.o
	
Parser.o : Parser.cpp Parser.hpp
	g++ -std=c++11 -c -o Parser.o Parser.cpp
	
Line.o : Line.hpp Line.cpp
	g++ -std=c++11 -c -o Line.o Line.cpp
	
ForLine.o : ForLine.hpp ForLine.cpp
	g++ -std=c++11 -c -o ForLine.o ForLine.cpp
	
ControlStructure.o : ControlStructure.hpp ControlStructure.cpp Segment.hpp
	g++ -std=c++11 -c -o ControlStructure.o ControlStructure.cpp

Loop.o : Loop.hpp Loop.cpp ControlStructure.hpp
	g++ -std=c++11 -c -o Loop.o Loop.cpp

Conditional.o : Conditional.hpp Conditional.cpp ControlStructure.hpp
	g++ -std=c++11 -c -o Conditional.o Conditional.cpp
	
Program.o : Program.hpp Program.cpp Segment.hpp
	g++ -std=c++11 -c -o Program.o Program.cpp
	
Segment.hpp : Statement.hpp

ide : GUI.class Threader.class
	javac GUI.java Threader.java
	jar -cvfe IBScript.jar GUI GUI*.class Threader*.class
	
GUI.class : GUI.java
	javac GUI.java
	
Threader.class : Threader.java
	javac Threader.java
	
clean :
	rm *.o
	rm *.exe
	rm *.class
	rm *.jar
	rm build/*
	
prepareForSubmission : all
	cp ibscript.exe IBScript.jar IBScriptSubmit
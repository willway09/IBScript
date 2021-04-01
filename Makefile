SRC = Array.cpp ArrayVariable.cpp CommaList.cpp Conditional.cpp ControlStructure.cpp ForLine.cpp Function.cpp Interpreter.cpp LanguageCollection.cpp LanguageQueue.cpp LanguageStack.cpp Line.cpp Loop.cpp Operator.cpp Parser.cpp Program.cpp Tokenizer.cpp Types.cpp Variable.cpp VariableHashMap.cpp VariableName.cpp
OBJ = ${SRC:.cpp=.o}
OBJ += DataStructures/ListException.o
#LIB = 

CPPFLAGS = -std=c++11 -g 

all: ${OBJ} ide
	make -C DataStructures
	g++ ${CPPFLAGS} -o ibscript ${OBJ} #${LIB}
	

ide : GUI.class Threader.class
	javac GUI.java Threader.java
	jar -cvfe IBScript.jar GUI GUI*.class Threader*.class
	
GUI.class : GUI.java
	javac GUI.java
	
Threader.class : Threader.java
	javac Threader.java


${OBJ}: %.o: %.cpp %.hpp

quick: ${OBJ}

clean:
	-rm *.o
	-rm *.class
	-rm *.jar
	-rm build/*
	-rm ibscript
	-make -C DataStructures clean

#zip:
	#zip Mccoy.Richard.Project3.zip *.cpp *.hpp

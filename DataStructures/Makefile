SRC = ListException.cpp 
OBJ = ${SRC:.cpp=.o}

CPPFLAGS = -std=c++11 -g 

${OBJ}: %.o: %.cpp %.hpp

quick: ${OBJ}

clean:
	-rm *.o
	-rm *.exe

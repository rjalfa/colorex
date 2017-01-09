CC = g++ -std=c++11
SRC = src/
LIBS = -lglut -lGL

LIB_UI = -lglui -lGLEW

assignment:
	mkdir -p bin/
	$(CC) -Wall $(SRC)assignment.cpp -o bin/assignment.o $(LIBS) $(LIB_UI)

all: first second assignment

first:
	mkdir -p bin/
	$(CC) $(SRC)first.cpp -o bin/first.o $(LIBS)

second:
	mkdir -p bin/
	$(CC) $(SRC)second.cpp -o bin/second.o $(LIBS) $(LIB_UI)	

clean:
	rm -rf bin/

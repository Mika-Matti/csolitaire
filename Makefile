all: compile link clean

compile:
	g++ -I src/include -c src/main.cpp 
	g++ -I src/include -c src/objectpositioner.cpp
link:
	g++ objectpositioner.o main.o -o game -L src/lib -l sfml-graphics -l sfml-window -l sfml-system
clean:
	rm -f $(wildcard *.o)

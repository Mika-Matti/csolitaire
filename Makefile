all: compile link clean

compile:
	g++ -I src/include -c src/gamefunctions.cpp
	g++ -I src/include -c src/card.cpp
	g++ -I src/include -c src/objectpositioner.cpp
	g++ -I src/include -c src/main.cpp
link:
	g++ gamefunctions.o card.o objectpositioner.o main.o -o game -lstdc++fs -L src/lib -l sfml-graphics -l sfml-window -l sfml-system
clean:
	rm -f $(wildcard *.o)

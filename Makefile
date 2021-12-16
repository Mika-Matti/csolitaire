all: compile link

compile:
	g++ -I src/include -c main.cpp 
	g++ -I src/include -c objectpositioner.cpp
link:
	g++ objectpositioner.o main.o -o main -L src/lib -l sfml-graphics -l sfml-window -l sfml-system

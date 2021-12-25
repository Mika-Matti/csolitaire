all: compile link clean

compile:
	g++ -I src/include -c src/card.cpp
	g++ -I src/include -c src/objectpositioner.cpp
	g++ -I src/include -c src/main.cpp
link:
	g++ card.o objectpositioner.o main.o -o game -static-libgcc -static-libstdc++ -lstdc++fs -L src/lib -l sfml-graphics -l sfml-window -l sfml-system
clean:
	rm -f $(wildcard *.o)

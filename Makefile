all: compile link clean

compile:
	windres src/icon.rc -O coff -o src/icon.res
	g++ -I src/include -c src/gamefunctions.cpp
	g++ -I src/include -c src/popup.cpp
	g++ -I src/include -c src/card.cpp
	g++ -I src/include -c src/objectpositioner.cpp
	g++ -I src/include -c src/main.cpp
link:
	g++ gamefunctions.o popup.o card.o objectpositioner.o src/icon.res main.o -o csolitaire -lstdc++fs -L src/lib -l sfml-graphics -l sfml-window -l sfml-system #-mwindows
clean:
	rm -f $(wildcard *.o)

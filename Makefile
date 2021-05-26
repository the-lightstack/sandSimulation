test:
	rm -f ./sandAnimation
	g++ ./program.cpp -g -o sandAnimation -lSDL

install:
	g++ ./program.cpp -o sandAnimation -lSDL

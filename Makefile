test:
	rm -f ./sandAnimation
	g++ ./program.cpp -o sandAnimation -lSDL2

install:
	g++ ./program.cpp -o sandAnimation -lSDL2

test:
	rm -f ./sandAnimation
	g++ ./program.cpp -o sandAnimation -lSDL

install:
	g++ ./program.cpp -o sandAnimation -lSDL

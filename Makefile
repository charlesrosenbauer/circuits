all:
	clang -O3	-lSDL2	src/*.c -o circ

debug:
	clang -Og -g	-lSDL2	src/*.c -o circ

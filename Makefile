all:
	clang -O3	src/*.c -o circ

debug:
	clang -Og -g	src/*.c -o circ

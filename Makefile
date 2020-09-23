v3test: v3test.o v3math.o
	gcc -o v3test v3math.o v3test.o

v3test.o: v3test.c v3math.h
	gcc -c v3test.c

v3math.o: v3math.c v3math.h
	gcc -c v3math.c
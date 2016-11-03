CFLAGS = -g -Wall -O3

project: main.o vector.o  parsing.o sort.o secondmode.o
	gcc $(CFLAGS)  bin/main.o bin/vector.o bin/parsing.o bin/sort.o bin/secondmode.o -o bin/project

main.o: src/main.c
	gcc $(CFLAGS)  src/main.c -c -o bin/main.o

vector.o: src/vector.c
	gcc $(CFLAGS)  src/vector.c -c -o bin/vector.o

parsing.o: src/parsing.c 
	gcc $(CFLAGS)  src/parsing.c -c -o bin/parsing.o

sort.o: src/sort.c 
	gcc $(CFLAGS)  src/sort.c -c -o bin/sort.o

secondmode.o: src/secondmode.c
	gcc $(CFLAGS)  src/secondmode.c -c -o bin/secondmode.o

clean:
	rm  bin/project bin/*.o

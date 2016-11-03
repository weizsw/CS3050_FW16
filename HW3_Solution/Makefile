CFLAGS = -g -Wall -O3

project: main.o vector.o  parsing.o stack.o graph.o
	gcc $(CFLAGS)  bin/main.o bin/vector.o bin/parsing.o bin/stack.o bin/graph.o -o bin/project

main.o: src/main.c
	gcc $(CFLAGS)  src/main.c -c -o bin/main.o

vector.o: src/vector.c
	gcc $(CFLAGS)  src/vector.c -c -o bin/vector.o

stack.o: src/stack.c
	gcc $(CFLAGS)  src/stack.c -c -o bin/stack.o

graph.o: src/graph.c
	gcc $(CFLAGS)  src/graph.c -c -o bin/graph.o

parsing.o: src/parsing.c 
	gcc $(CFLAGS)  src/parsing.c -c -o bin/parsing.o

clean:
	rm  bin/project bin/*.o

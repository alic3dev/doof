CC=gcc
objectFolder=./build/objects
objects=main.o

doof: $(objects)
	$(CC) $(objectFolder)/main.o -o doof

main.o: main.c
	$(CC) -c main.c -o $(objectFolder)/main.o
 

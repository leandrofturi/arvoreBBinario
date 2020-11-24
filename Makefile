all:
	gcc -g -Wall cod/*.c main.c -o trab3

clean:
	rm -f *.o trab3

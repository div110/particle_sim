all:
	gcc main.c -lSDL2
debug:
	gcc -g main.c -lSDL2
clean:
	rm ?.out


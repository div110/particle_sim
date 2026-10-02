all:
	gcc main.c quadlib.c -lSDL2
debug:
	gcc -g main.c quadlib.c -lSDL2
clean:
	rm ?.out


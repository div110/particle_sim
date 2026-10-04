all:
	gcc main.c quadlib.c collisions.c -lSDL2
debug:
	gcc -g main.c quadlib.c collisions.c -lSDL2
clean:
	rm ?.out


all:
	gcc main.c quadlib.c collisions.c -lSDL2 -lm
debug:
	gcc -g main.c quadlib.c collisions.c -lSDL2 -lm
clean:
	rm ?.out


all:
	gcc -O3 main.c quadlib.c collisions.c particles.c -lSDL2 -lm
debug:
	gcc -g main.c quadlib.c collisions.c particles.c -lSDL2 -lm
clean:
	rm ?.out


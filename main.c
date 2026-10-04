#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "quadlib.h"

uint16_t size_x = 680;
uint16_t size_y = 420;


int main(){
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Init( SDL_INIT_VIDEO );
	SDL_CreateWindowAndRenderer( size_x, size_y, 0, &window, &renderer );

	SDL_Event event;

	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear( renderer );

	//setting quadtree
	struct QuadTree tree = { NULL, 4 };

	//setting particles
	int amount = 20;
	struct Particle *cells = calloc( sizeof( struct Particle ), amount );
	SDL_Rect rectangles[amount];
	
	for( int i = 0; i < amount; i++ ){ 
		cells[i].position_x = rand() % size_x;
		cells[i].position_y = rand() % size_y;
		cells[i].velocity_x = rand() % 10 - 5;
		cells[i].velocity_y = rand() % 10 - 5;

		rectangles[i].w = 3;
		rectangles[i].h = 3;

		quad_insert( &tree, &cells[i] );
	}
	



	
	//setting time
	uint32_t time_start;
	uint16_t delta;
	while( true ){
		time_start = SDL_GetTicks();
		SDL_RenderClear( renderer );
		SDL_SetRenderDrawColor( renderer, 255, 100, 100, 255 );

		for( int i = 0; i < amount; i++ ){
			cells[i].position_x = ( cells[i].position_x + cells[i].velocity_x );
			cells[i].position_y = ( cells[i].position_y + cells[i].velocity_y );
			rectangles[i].x = cells[i].position_x - 1;
			rectangles[i].y = cells[i].position_y - 1;

			if ( cells[i].position_x < 0 || cells[i].position_x > size_x ){ cells[i].velocity_x *= -1; }
			if ( cells[i].position_y < 0 || cells[i].position_y > size_y ){ cells[i].velocity_y *= -1; }
		}

		SDL_RenderFillRects( renderer, rectangles, amount );
		SDL_RenderPresent( renderer );


		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		
		delta = SDL_GetTicks() - time_start; 
		if ( delta < 16 ){ SDL_Delay( 16 - delta ); }
	}

	return 0;
	
}

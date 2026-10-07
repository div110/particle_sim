#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>

#include "quadlib.h"
#include "collisions.h"


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
	struct QuadTree tree = { NULL, 16 };

	//setting particles
	int amount = 5000;
	struct Particle *cells = malloc( sizeof( struct Particle ) * amount );
	assert( cells );
	SDL_Rect rectangles[amount];
	
	for( int i = 0; i < amount; i++ ){ 
		cells[i].position_x = rand() % size_x;
		cells[i].position_y = rand() % size_y;
		cells[i].velocity_x = (rand() % 100 - 50) / (float)100;
		cells[i].velocity_y = (rand() % 100 - 50) / (float)100;

		rectangles[i].w = 3;
		rectangles[i].h = 3;
	}


	
	
	//setting time
	uint32_t time_start;
	uint16_t delta;
	while( true ){
		time_start = SDL_GetTicks();
		SDL_RenderClear( renderer );
		SDL_SetRenderDrawColor( renderer, 128, 128, 128, 255 );

		for ( uint16_t i = 0; i < amount; i++ ){

			cells[i].position_x = ( cells[i].position_x + cells[i].velocity_x );
			cells[i].position_y = ( cells[i].position_y + cells[i].velocity_y );
			rectangles[i].x = cells[i].position_x - 1;
			rectangles[i].y = cells[i].position_y - 1;

			if ( cells[i].position_x < 0 || cells[i].position_x > size_x ){ cells[i].velocity_x *= -1; }
			if ( cells[i].position_y < 0 || cells[i].position_y > size_y ){ cells[i].velocity_y *= -1; }
		}


		struct Particle *particle = NULL;
		for ( uint16_t i = 0; i < amount; i++ ){
			particle = collision_detection( tree.root, &cells[i] );
			if ( particle ){ collide( particle, &cells[i] );}
			assert( quad_insert( &tree, &cells[i] ) );
		}

		quad_free( tree.root );
		tree.root = NULL;
		

		SDL_RenderFillRects( renderer, rectangles, amount );
		SDL_RenderPresent( renderer );


		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
		
		delta = SDL_GetTicks() - time_start; 
		if ( delta < 8 ){ SDL_Delay( 8 - delta ); }
	}

	return 0;
	
}

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <assert.h>
#include <stdio.h>
#include <pthread.h>

#include "quadlib.h"
#include "collisions.h"
#include "particles.h"


uint16_t size_x = 680;
uint16_t size_y = 420;


int main(){
	SDL_Event event;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	SDL_Init( SDL_INIT_VIDEO );
	SDL_CreateWindowAndRenderer( size_x, size_y, 0, &window, &renderer );


	SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );
	SDL_RenderClear( renderer );

	//setting quadtree
	struct QuadTree tree = { NULL, 128 };

	//setting particles
	uint32_t amount = 5000;
	struct Particle *cells = malloc( sizeof( struct Particle ) * amount );
	assert( cells );
	SDL_Rect rectangles[amount];
	
	for( int i = 0; i < amount; i++ ){ 
		cells[i].position_x = rand() % size_x;
		cells[i].position_y = rand() % size_y;
		cells[i].velocity_x = (rand() % 100 - 50) / (float)100;
		cells[i].velocity_y = (rand() % 100 - 50) / (float)100;

		rectangles[i].w = 1;
		rectangles[i].h = 1;
	}

	
	
	//setting time
	uint32_t time_start;
	uint16_t delta;
	bool button_down = false;
	bool button_side = false;
	uint16_t button_x;
	uint16_t button_y;
	while( true ){
		time_start = SDL_GetTicks();
		SDL_RenderClear( renderer );
		SDL_SetRenderDrawColor( renderer, 200, 200, 200, 255 );
		SDL_PollEvent( &event );

		switch( event.type ){
			case SDL_MOUSEBUTTONDOWN:
				button_down = true;
				button_x = event.button.x;
				button_y = event.button.y;
				button_side = ( event.button.button == SDL_BUTTON_LEFT ) ? false : true;
				break;
			case SDL_MOUSEBUTTONUP:
				button_down = false;
				break;
			case SDL_MOUSEMOTION:
				button_x = event.motion.x;
				button_y = event.motion.y;
				break;
		}


		if ( button_down && !button_side ){ attract_particles( cells, amount, button_x, button_y ); }
		else if ( button_down && button_side ){ repel_particles( cells, amount, button_x, button_y ); }
		update_particles( cells, rectangles, amount, size_x, size_y );


		struct Particle *particle = NULL;
		for ( uint32_t i = 0; i < amount; i++ ){
			particle = collision_detection( tree.root, &cells[i] );
			if ( particle ){ collide( particle, &cells[i] ); }
			assert( quad_insert( &tree, &cells[i] ) );
		}
		
		quad_free( tree.root );
		tree.root = NULL;

		
		SDL_RenderFillRects( renderer, rectangles, amount );
		SDL_RenderPresent( renderer );


		SDL_SetRenderDrawColor( renderer, 0, 0, 0, 255 );

		delta = SDL_GetTicks() - time_start; 
		if ( delta < 16 ){ SDL_Delay( 16 - delta ); }
	}

	return 0;
}

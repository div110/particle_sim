#include <stdint.h>
#include <SDL2/SDL.h>

#include "quadlib.h"


void move_particles( struct Particle *particles, SDL_Rect *rectangles, uint32_t amount, uint16_t w, uint16_t h ){
	struct Particle *body;
	for( uint32_t i = 0; i < amount; i++ ){
		struct Particle *body = &particles[i];
		body->position_x += body->velocity_x;
		body->position_y += body->velocity_y;

		rectangles[i].x = body->position_x;
		rectangles[i].y = body->position_y;

		if ( body->position_x < 0 || body->position_x > w ){ body->velocity_x *= -1; }
		if ( body->position_y < 0 || body->position_y > h - 3 ){ body->velocity_y *= -0.3f; }

		if ( !( body->position_y > h - 3 ) ){ body->velocity_y += 0.1f; }
	}
}

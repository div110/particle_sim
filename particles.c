#include <stdint.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "particles.h"
#include "quadlib.h"


void update_particles( struct Particle *particles, SDL_Rect *rectangles, uint32_t amount, uint16_t w, uint16_t h ){
	struct Particle *body;
	for ( uint32_t i = 0; i < amount; i++ ){
		struct Particle *body = &particles[i];
		body->position_x += body->velocity_x;
		body->position_y += body->velocity_y;

		rectangles[i].x = body->position_x;
		rectangles[i].y = body->position_y;

		if ( body->position_x < 0 || body->position_x > w ){ body->velocity_x *= -1.0f; }
		if ( body->position_y < 0 || body->position_y > h - 3 ){ body->velocity_y *= -1.0f; }

		//if ( !( body->position_y > h - 3 ) ){ body->velocity_y += 0.1f; }
	}
}

void *update_particles_thread( void *void_pi ){
	struct ParticlesInfo *pi = (struct ParticlesInfo *)void_pi;
	update_particles( pi->particles, pi->rectangles, pi->amount, pi->w, pi->h );
	return NULL;
}



void attract_particles( struct Particle *particles, uint32_t amount, uint16_t x, uint16_t y ){ 
	float dx, dy, length;
	for ( uint32_t i = 0; i < amount; i++ ){
		dx = x - particles[i].position_x;
		dy = y - particles[i].position_y;
		length = hypot( dx, dy );

		dx /= length;
		dy /= length;

		//particles[i].velocity_x += dx;
		//particles[i].velocity_y += dy;
		particles[i].position_x += dx;
		particles[i].position_y += dy;	
	}
}

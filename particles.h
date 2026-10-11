#ifndef PARTICLES_H_
#define PARTICLES_H_

struct ParticlesInfo {
	struct Particle *particles;
	SDL_Rect *rectangles;
	uint32_t amount;
	uint16_t w;
	uint16_t h;
};


void update_particles( struct Particle *particles, SDL_Rect *rectangles, uint32_t amount, uint16_t w, uint16_t h );
void *update_particles_thread( void *void_pi );
void attract_particles( struct Particle *particles, uint32_t amount, uint16_t x, uint16_t y );
void repel_particles( struct Particle *particles, uint32_t amount, uint16_t x, uint16_t y );

#endif

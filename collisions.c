#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "quadlib.h"



bool is_collision( struct Particle *p1, struct Particle *p2 ){
	float dx = p1->position_x - p2->position_x;
	float dy = p1->position_y - p2->position_y;
        return ( fabs( dx * dx ) <= 3 ) \
	&& ( fabs( dy * dy ) <= 3 );
}

struct Particle *collision_detection( struct QuadNode *node, struct Particle *particle ){
        if ( !node || !particle ){ return NULL; }

        for ( uint16_t i = 0; i < node->p_index; i++ ){
                if ( is_collision( particle, node->particles[i] ) ){ return node->particles[i]; }
        }

        bool left = ( particle->position_x < node->position_x ) ? true : false;
        bool top = ( particle->position_y < node->position_y ) ? true : false;

        if ( left && top ){ return collision_detection( node->tl, particle ); }
        else if ( left && !top ){ return collision_detection( node->tr, particle ); }
        else if ( !left && top ){ return collision_detection( node->bl, particle ); }
        else if ( !left && !top ){ return collision_detection( node->br, particle ); }
        else { exit(1); }
}


void collide( struct Particle *p1, struct Particle *p2 ){

	float relative_x = p1->velocity_x - p2->velocity_x;
	float relative_y = p1->velocity_y - p2->velocity_y;
	float r_length = hypot( relative_x, relative_y );

	float normal_x = relative_x / r_length;
	float normal_y = relative_y / r_length;

	float dot_rn = relative_x * normal_x + relative_y * normal_y;

	p1->velocity_x -= dot_rn * normal_x;
	p1->velocity_y -= dot_rn * normal_y;

	p2->velocity_x += dot_rn * normal_x;
	p2->velocity_y += dot_rn * normal_y;


	p1->velocity_x *= 0.9f;
	//p1->velocity_y *= 0.9f;
	p2->velocity_x *= 0.9f;
	//p2->velocity_y *= 0.9f;
}

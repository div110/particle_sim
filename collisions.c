#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "quadlib.h"

bool is_collision( struct Particle *p1, struct Particle *p2 ){
        return ( p1->position_x == p2->position_x ) && ( p1->position_y && p2->position_y );
}

struct Particle *collision_detection( struct QuadNode *node, struct Particle *particle ){
        if ( !node || !particle ){ return NULL; }

        for ( uint8_t i = 0; i < node->p_index; i++ ){
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
	p1->velocity_x *= -1;
	p1->velocity_y *= -1;
	p2->velocity_x *= -1;
	p2->velocity_y *= -1;
}

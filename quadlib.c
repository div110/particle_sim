#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "quadlib.h"




struct QuadNode *make_quadnode( uint32_t length ){  
	struct QuadNode *node = malloc( sizeof( struct QuadNode ) );
	if ( !node ){ return NULL; }

	node->is_leaf = true;
	node->tl = NULL;
	node->tr = NULL;
	node->bl = NULL;
	node->br = NULL;

	node->particles = malloc( sizeof( struct Particle ) * length );
	if ( !node->particles ){ free( node ); return NULL; }
	node->p_index = 0;
	node->p_length = length;

	return node;
}



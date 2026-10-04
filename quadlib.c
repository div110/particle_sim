#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "quadlib.h"

//
#include <stdio.h>


bool is_equal( struct Particle p1, struct Particle p2 ){
	return p1.velocity_x == p2.velocity_x && p1.velocity_y == p2.velocity_y \
		&& p1.position_x == p2.position_x && p1.position_y == p2.position_y;
}

struct QuadNode *make_quadnode( uint16_t center_x, uint16_t center_y ,uint32_t length ){  
	struct QuadNode *node = malloc( sizeof( struct QuadNode ) );
	if ( !node ){ return NULL; }

	node->position_x = center_x;
	node->position_y = center_y;

	node->tl = NULL;
	node->tr = NULL;
	node->bl = NULL;
	node->br = NULL;

	node->particles = malloc( sizeof( struct Particle * ) * length );
	if ( !node->particles ){ free( node ); return NULL; }
	node->p_index = 0;
	node->p_length = length;

	return node;
}

bool insert_rec( struct QuadNode *node, struct Particle *particle ){
	bool left = ( particle->position_x < node->position_x ) ? true : false;
	bool top = ( particle->position_y < node->position_y ) ? true : false;

	if ( node->p_index < node->p_length ) { 
		node->particles[node->p_index] = particle; 
		node->p_index++; 
		return true;
	}
	

	struct QuadNode **next_node;
	if ( left && top ){ next_node = &node->tl; }
	else if ( left && !top ){ next_node = &node->bl; }
	else if ( !left && top ){ next_node = &node->tr; }
	else if ( !left && !top ){ next_node = &node->br; }
	else { exit(1); }

	if ( !*next_node ){ *next_node = make_quadnode( \
		node->position_x + ( node->position_x / 2 ) * ( top ) ? -1 : 1,\
		node->position_y + ( node->position_y / 2 ) * ( left ) ? -1 : 1,\
		node->p_length ); 
	}

	if ( !*next_node ){ return false; }

	return insert_rec( *next_node, particle );
}

bool quad_insert( struct QuadTree *tree, struct Particle *particle ){
	if ( !tree || !particle ){ return false; }
	if ( !tree->root ){ 
		tree->root = make_quadnode( 340, 210, tree->capacity ); // TODO !const
		if( !tree->root ){ return false; }
	}

	return insert_rec( tree->root, particle );
}

void quad_remove_particle( struct QuadNode *node, struct Particle *particle ){
	uint8_t i = 0;
	for ( ; i < node->p_index; i++ ){
		if ( node->particles[ i ] == particle  ){ break; }// TODO	
	}

	for ( node->p_index - 1; i < node->p_index - 1; i++ ){
		node->particles[ i ] = node->particles[i + 1];
	}
}

struct QuadNode *quad_find( struct QuadNode *node, struct Particle *particle ){
	if ( !node ){ return NULL; }
	for ( uint8_t i = 0; i < node->p_index; i++ ){
		if ( node->particles[ i ] == particle  ){ return node; }
	}

	bool left = ( particle->position_x < node->position_x ) ? true : false ;
	bool top = ( particle->position_y < node->position_y ) ? true : false;

	if ( top && left ){ return quad_find( node->tl, particle ); }
	else if ( top && !left ){ return quad_find( node->tr, particle); }
	else if ( !top && left ){ return quad_find( node->bl, particle); }
	else if ( !top && !left ){ return quad_find( node->br, particle); }
	else { exit(1); }
}

void quad_print( struct QuadNode *node ){
	if ( !node ){ return; }

	for ( uint8_t i = 0; i < node->p_index; i++ ){
		printf("%p\n", node->particles[i]);
		printf("----------------\n");
	}
	
	quad_print(node->tl);
	quad_print(node->tr);
	quad_print(node->bl);
	quad_print(node->br);
}

#ifndef QUADLIB_H_
#define QUADLIB_H_

//TODO
struct Particle {
        int8_t velocity_x;
        int8_t velocity_y;

        uint16_t position_x;
        uint16_t position_y;
};

struct QuadTree {
	struct QuadNode *root;
	uint32_t capacity;
};

struct QuadNode {
	uint16_t position_x;
	uint16_t position_y;

        struct QuadNode *tl;
        struct QuadNode *tr;
        struct QuadNode *bl;
        struct QuadNode *br;

        struct Particle **particles; //goes here if between quadrants
        uint32_t p_index;
	uint32_t p_length;
};

struct QuadNode *make_quadnode ( uint16_t center_x, uint16_t center_y, uint32_t length );
bool insert_rec( struct QuadNode *node, struct Particle *particle );
bool quad_insert( struct QuadTree *tree, struct Particle *particle );
void quad_remove_particle( struct QuadNode *node, struct Particle *particle );
struct QuadNode *quad_find( struct QuadNode *node, struct Particle *particle );
void quad_print( struct QuadNode *node );
#endif

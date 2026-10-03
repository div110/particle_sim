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
	//uint16_t position_x;
	//uint16_t position_y;
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
#endif

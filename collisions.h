#ifndef COLLISIONS_H_
#define COLLISIONS_H_

struct Particle *collision_detection( struct QuadNode *node, struct Particle *particle );
bool is_collision( struct Particle *p1, struct Particle *p2 );
void collide( struct Particle *p1, struct Particle *p2 );

#endif

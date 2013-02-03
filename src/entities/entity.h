#pragma once

#include <stdbool.h>

#include <SDL/SDL.h>
#include <chipmunk/chipmunk.h>

typedef enum EntityKind {
  PARTICLEKIND,
  BLOCKKIND,
  RINGKIND
} EntityKind;

typedef struct Entity {
  EntityKind kind;
  Uint32 color;
  Uint16 life;
  cpBody* body;
  cpShape* shape;
} Entity;

extern Entity* mkentity_particle(cpSpace* space, cpVect position,
    cpVect impulse);

extern Entity* mkentity_block(cpSpace* space, cpVect position,
    cpFloat width, cpFloat height, cpFloat mass, cpVect velocity);

extern Entity* mkentity_ring(cpSpace* space, cpVect position,
    cpFloat radius, cpFloat mass, cpVect velocity);

extern void delentity(Entity* entity);

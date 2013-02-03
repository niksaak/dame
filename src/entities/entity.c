#include "entity.h"

#ifndef PARTICLE_DEFAULT_LIFE
#define PARTICLE_DEFAULT_LIFE 1000
#endif

static Entity* alloc_entity()
{
  return malloc(sizeof(Entity));
}

Entity* mkentity_particle(cpSpace* space, cpVect position, cpVect impulse)
{
  Entity* ent = alloc_entity();

  ent->kind = PARTICLEKIND;
  ent->color = 0xffffffff;
  ent->life = PARTICLE_DEFAULT_LIFE;
  ent->body = cpBodyNew(0.01, cpMomentForCircle(0.01, 0, 1, cpvzero));
  ent->shape = cpCircleShapeNew(ent->body, 1, cpvzero);
  cpSpaceAddBody(space, ent->body);
  cpSpaceAddShape(space, ent->shape);
  cpBodySetPos(ent->body, position);
  cpBodyApplyImpulse(ent->body, impulse, cpvzero);
  cpBodySetUserData(ent->body, ent);
  cpShapeSetUserData(ent->shape, ent);

  return ent;
}

Entity* mkentity_block(cpSpace* space, cpVect position,
    cpFloat width, cpFloat height, cpFloat mass, cpVect velocity)
{
  Entity* ent = alloc_entity();

  ent->kind = BLOCKKIND;
  ent->color = 0xffffff;
  ent->body = cpBodyNew(mass, cpMomentForBox(mass, width, height));
  ent->shape = cpBoxShapeNew(ent->body, width, height);
  cpSpaceAddBody(space, ent->body);
  cpSpaceAddShape(space, ent->shape);
  cpBodySetPos(ent->body, position);
  cpSpaceReindexShapesForBody(space, ent->body);
  cpBodySetVel(ent->body, velocity);
  cpBodySetUserData(ent->body, ent);
  cpShapeSetUserData(ent->shape, ent);

  return ent;
}

Entity* mkentity_ring(cpSpace* space, cpVect position,
    cpFloat radius, cpFloat mass, cpVect velocity)
{
  Entity* ent = alloc_entity();

  ent->kind = RINGKIND;
  ent->color = 0xffffff;
  ent->body = cpBodyNew(mass, cpMomentForCircle(mass, 0, radius, cpvzero));
  ent->shape = cpCircleShapeNew(ent->body, radius, cpvzero);
  cpSpaceAddBody(space, ent->body);
  cpSpaceAddShape(space, ent->shape);
  cpBodySetPos(ent->body, position);
  cpSpaceReindexShapesForBody(space, ent->body);
  cpBodySetVel(ent->body, velocity);
  cpBodySetUserData(ent->body, ent);
  cpShapeSetUserData(ent->shape, ent);

  return ent;
}

void delentity(Entity* e)
{
  if(e != NULL) {
    cpSpaceRemoveBody(cpBodyGetSpace(e->body), e->body);
    cpSpaceRemoveShape(cpShapeGetSpace(e->shape), e->shape);
    cpBodyFree(e->body);
    cpShapeFree(e->shape);
    free(e);
  }
}

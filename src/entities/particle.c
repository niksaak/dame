#include "particle.h"

Entity* ent_emit_particle(cpSpace* space, cpBody* body,
    cpVect offset, cpVect impulse)
{
  return mkentity_particle(space,
      cpvadd(cpBodyLocal2World(body, offset), cpBodyGetPos(body)),
      impulse);
}

Entity* ent_emit_particlea(cpSpace* space, cpBody* body,
    cpVect offset, cpFloat angle, cpFloat velocity)
{
  return mkentity_particle(space,
      cpvadd(cpBodyLocal2World(body, offset), cpBodyGetPos(body)),
      cpv(velocity * cos(angle), velocity * sin(angle)));
}


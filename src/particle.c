#include "particle.h"

#include <math.h>
#include "sys.h"

// moment of inertia for circle: (pi/4)*r^4
cpFloat particle_r = 0.01;
cpFloat particle_moi = 7.85398 * 10e-14 ?: 0.000000001;
int id;
particle_t* particles;

int mkparticle(particle_kind_t kind, cpVect pos, cpVect impulse, double energy)
{
  particle_t* p = malloc(sizeof *p);
  if(p == NULL) {
    return -1; // bad malloc
  }
  cpSpace* space = current_space();
  cpBody* body = cpBodyNew(energy / 1000.0, particle_moi);
  cpShape* shape = cpCircleShapeNew(body, particle_r, cpvzero);

  cpBodySetUserData(body, p);
  cpShapeSetUserData(shape, p);
  cpSpaceAddBody(space, body);
  cpSpaceAddShape(space, shape);
  *p = (particle_t){
    .id = id,
    .kind = kind,
    .energy = energy,
    .life = energy,
    .body = body
  };
  HASH_ADD_INT(particles, id, p);

  return id++;
}

int kmparticle(int id)
{
  particle_t* p = particle(id);
  if(p == NULL) {
    return -1;
  }

  HASH_DEL(particles, p);
  remove_body(p->body);
  free(p);

  return 0;
}

particle_t* particle(int id)
{
  particle_t* p;

  HASH_FIND_INT(particles, &id, p);

  return p;
}

int draw_particles(void)
{
  return -1; // TODO
}


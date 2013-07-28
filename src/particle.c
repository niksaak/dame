#include "particle.h"

#include <math.h>
#include "sys.h"
#include "vector.h"
#include "draw.h"

// moment of inertia for circle: (pi/4)*r^4
cpFloat particle_r = 0.01;
cpFloat particle_moi = 7.85398 * 10e-14 ?: 0.000000001;
int id = 0;
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
  static Vec pointv[512];
  static size_t pointc = ARRLEN(pointv, Vec);
  double z = zoom();
  particle_t* p = particles;
  int i = 0;
  size_t count = HASH_COUNT(particles);

  while(i < count) {
    for(; p != NULL && i < pointc; p = p->hh.next, i++) {
      cpVect pos = cpBodyGetPos(p->body);

      if(fabs(pos.x) <= z / 2 && fabs(pos.y) <= z / 2) {
        // rough check if position is inside screen borders
        // TODO: possibly make it separate function
        // TODO: possibly use HASH_SELECT
        pointv[i] = cpv2vec(pos);
      }
    }
    if(draw_points(pointv, i % pointc)) {
      return -1;
    }
  }

  return 0;
}

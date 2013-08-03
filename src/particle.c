#include "particle.h"

#include <math.h>
#include "sys.h"
#include "vector.h"
#include "draw.h"

// moment of inertia for circle: (pi/4)*r^4
static const cpFloat particle_r = 0.01;
static const cpFloat particle_moi = 7.85398 * 10e-14;

static int id = 0;
static particle_t* particles;

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

int kmparticle_id(int id)
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

int kmparticle_ptr(particle_t* p)
{
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
        pointv[i] = cpv2vec(pos);
      }
    }
    if(draw_points(pointv, i % pointc)) {
      return -1;
    }
  }

  return 0;
}

void age_particles(void)
{
  particle_t* p = particles;
  particle_t* tmp;
  HASH_ITER(hh, particles, p, tmp) {
    if(p->life <= 0) {
      double enew = p->energy / (2 * floran());

      if(p->kind > COLD_PARTICLE) {
        p->kind--;
        p->energy = enew;
        p->life = (p->kind == COLD_PARTICLE) ? 0 : enew;
      } else {
        kmparticle(p);
      }
    }
    p->life--;
  }
}


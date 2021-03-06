#pragma once

/* PARTICLE
 * emitting particles
 */

#include <chipmunk/chipmunk.h>
#include "util.h"

typedef enum particle_kind_t {
  HOT_PARTICLE, // Scary
  WARM_PARTICLE, // Cozy
  COLD_PARTICLE // Harmless
} particle_kind_t;

typedef struct particle_t {
  int id;
  particle_kind_t kind;
  double energy; // particle max life
  double life; // particle current life
  cpBody* body;

  UT_hash_handle hh;
} particle_t;

int mkparticle(particle_kind_t kind, cpVect pos, cpVect impulse, double energy);

#define kmparticle(p)              \
  _Generic((p),                    \
      particle_t*: kmparticle_ptr, \
      int: kmparticle_id,          \
      void*: kmparticle_ptr)(p)

int kmparticle_id(int id);

int kmparticle_ptr(particle_t* ptr);

particle_t* particle(int id);

int draw_particles(void);

void age_particles(void);


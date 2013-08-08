#pragma once

/* UTILS
 * general convenience utilities
 */

#include <stdlib.h>
#include <math.h>

#include <GLFW/glfw3.h>
#include <uthash.h>

#define TO_STR(symbol) #symbol

#ifndef MAX
#define MAX(a, b)                       \
  _Generic( (a),                        \
      float: fmaxf(a, b),               \
      double: fmax(a, b),               \
      long double: fmaxl(a, b),         \
      default: ((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#define MIN(a, b)                       \
  _Generic( (a),                        \
      float: fminf(a, b),               \
      double: fmin(a, b),               \
      long double: fminl(a, b),         \
      default: ((a) < (b)) ? (a) : (b))
#endif

#define ARRLEN(arr, type) (sizeof arr / sizeof (type))

// PRECISION
static const double
PI = 3.1415926535897932384626433832795028841971693993751058209749,
QUADCIRCLE = 1.57079632679489661923132169163975144209858469968755,
SEMICIRCLE = PI,
TRIQUADCIRCLE = 4.7123889803846898576939650749192543262957540990;

int genid(void);

static inline double floran(void)
{ // floating rand
  return (double)rand()/(double)RAND_MAX;
}

inline int ran_domo(int min, int max)
{ // bounded rand
  int domo = rand();
  int range = max - min;
  int rem = RAND_MAX % range;
  int bucket = RAND_MAX / range;

  if(domo == RAND_MAX) {
    return ran_domo(min, max);
  }
  if(domo < RAND_MAX - rem) {
    return min + domo / bucket;
  }
  return ran_domo(min, max);
}

const char* gl_strerror(GLenum error);


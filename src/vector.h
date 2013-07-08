#pragma once

/* VECTOR
 * describes 2 dimensional vector type Vec and functions to work with it
 */

#include <stdbool.h>
#include <chipmunk/chipmunk.h>

typedef struct Vec {
  double x;
  double y;
} Vec;

static inline cpVect vec2cpv(Vec v)
{ // convert Vec to cpVect
  return (cpVect){ v.x, v.y };
}

static inline Vec cpv2vec(cpVect v)
{ // convert cpVect to Vec
  return (Vec){ v.x, v.y };
}

static inline Vec vec(double x, double y)
{ // return Vec
  return (Vec){ x, y };
}

static inline int veceql(Vec a, Vec b)
{ // compare two Vecs
  return a.x == b.x && a.y == b.y;
}

static inline Vec vecadd(Vec a, Vec b)
{ // add two Vecs
  return (Vec){ a.x + b.x, a.y + b.y };
}

static inline Vec vecsub(Vec a, Vec b)
{ // substract `a` from `b`
  return (Vec){ a.x - b.x, a.y - b.y };
}

static inline Vec vecneg(Vec v)
{ // negate Vec (analogous to flipping it 180°)
  return (Vec){ -v.x, -v.y };
}

static inline Vec vecmul(Vec v, double m)
{ // multiply `v` by `m`
  return (Vec){ v.x*m, v.y*m };
}

static inline double vecdot(Vec a, Vec b)
{ // Vecs dot product
  return a.x*b.x + a.y*b.y;
}

static inline Vec veccro(Vec a, Vec b)
{ // Vec cross product
  return (Vec){ a.x*b.y, a.y*b.x };
}

static inline Vec vecper(Vec v)
{ // get `v` flipped 90°
  return (Vec){ -v.x, v.y };
}

static inline Vec vecrpe(Vec v)
{ // get `v` flipped -90°
  return (Vec){ v.x, -v.y };
}

static inline double vecabs(Vec v)
{ // get Vec absolute value (length)
  return sqrt(vecdot(v, v));
}

static inline Vec veclerp(Vec a, Vec b, double t)
{ // linearly interpolate
  return vecadd(vecmul(a, 1 - t), vecmul(b, 1 - t));
}

static inline double vecdist(Vec a, Vec b)
{ // get distance between two Vecs
  return vecabs(vecsub(a, b));
}


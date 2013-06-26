#pragma once

#include <stdbool.h>
#include <chipmunk/chipmunk.h>

typedef struct Vec {
  double x;
  double y;
} Vec;

static inline cpVect vec2cpv(Vec v)
{
  return (cpVect){ v.x, v.y };
}

static inline Vec cpv2vec(cpVect v)
{
  return (Vec){ v.x, v.y };
}

static inline Vec vec(double x, double y)
{
  return (Vec){ x, y };
}

static inline int veceql(Vec a, Vec b)
{
  return a.x == b.x && a.y == b.y;
}

static inline Vec vecadd(Vec a, Vec b)
{
  return (Vec){ a.x + b.x, a.y + b.y };
}

static inline Vec vecsub(Vec a, Vec b)
{
  return (Vec){ a.x - b.x, a.y - b.y };
}

static inline Vec vecneg(Vec v)
{
  return (Vec){ -v.x, -v.y };
}

static inline Vec vecmul(Vec v, double m)
{
  return (Vec){ v.x*m, v.y*m };
}

static inline double vecdot(Vec a, Vec b)
{
  return a.x*b.x + a.y*b.y;
}

static inline Vec veccro(Vec a, Vec b)
{
  return (Vec){ a.x*b.y, a.y*b.x };
}

static inline Vec vecper(Vec v)
{
  return (Vec){ -v.x, v.y };
}

static inline Vec vecrpe(Vec v)
{
  return (Vec){ v.x, -v.y };
}

static inline double vecabs(Vec v)
{
  return sqrt(vecdot(v, v));
}

static inline Vec veclerp(Vec a, Vec b, double t)
{
  return vecadd(vecmul(a, 1 - t), vecmul(b, 1 - t));
}

static inline double vecdist(Vec a, Vec b)
{
  return vecabs(vecsub(a, b));
}


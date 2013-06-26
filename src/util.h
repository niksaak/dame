#pragma once

#include "stdlib.h"

#define TO_STR(symbol) #symbol

/* Not sure if I really need those: */
static inline long lmax(long a, long b)
{
  return (a > b) ? a : b;
}

static inline long lmin(long a, long b)
{
  return (a < b) ? a : b;
}

static inline unsigned long ulmax(unsigned long a, unsigned long b)
{
  return (a > b) ? a : b;
}

static inline unsigned long ulmin(unsigned long a, unsigned long b)
{
  return (a < b) ? a : b;
}

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


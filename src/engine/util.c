#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "util.h"

SDL_Point SDLpt(int x, int y)
{
  static SDL_Point pt;

  pt.x = x;
  pt.y = y;

  return pt;
}

SDL_Point cpvSDL(cpVect vector, SDL_Surface* target, cpVect offset)
{
  SDL_Point pt;

  pt.x = (target->w / 2) + vector.x - offset.x;
  pt.y = (target->h / 2) - vector.y + offset.y;

  return pt;
}

cpVect SDLcpv(SDL_Point point, SDL_Surface* target, cpVect offset)
{
  return cpvzero; // FIXME
}

bool nullp(const void* ptr)
{
  if(ptr == NULL)
    return true;
  return false;
}

void warn(const char* funname, const char* warning)
{
  fprintf(stderr, "%s: WARNING: %s\n", funname, warning);
}

void crash(const char* funname, const char* reason)
{
  if(nullp(reason))
    reason = strerror(errno);
  fprintf(stderr, "%s: CRUSHING ERROR: %s\n", funname, reason);
  exit(EXIT_FAILURE);
}

int ran_domo(Uint32 min, Uint32 max)
{
  int domo = rand();

  if(domo == RAND_MAX)
    return ran_domo(min, max);
  int range = max - min;
  int rem = RAND_MAX % range;
  int bucket = RAND_MAX / range;

  if(domo < RAND_MAX - rem)
    return min + domo / bucket;
  return ran_domo(min, max);
}

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "util.h"

SDL_Point cpvSDL(cpVect vector, SDL_Surface* target, cpVect offset)
{
  SDL_Point pt;

  pt.x = (target->w / 2) + vector.x - offset.x;
  pt.y = (target->h / 2) - vector.y + offset.y;

  return pt;
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

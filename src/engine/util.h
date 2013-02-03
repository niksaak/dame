#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include <SDL/SDL.h>
#include <chipmunk/chipmunk.h>

#ifdef DEBUG_MODE
#include <stdio.h>
#define DEBUG(...) \
  fprintf(stderr, __VA_ARGS__);
#endif

#define WARN(w) \
  warn(__func__, w);

#define CRASH(r) \
  crash(__func__, r);

typedef struct SDL_point {
  int x;
  int y;
} SDL_Point;

extern SDL_Point SDLpt(int x, int y);

extern SDL_Point cpvSDL(cpVect vector, const SDL_Surface* target, cpVect offset);

extern cpVect SDLcpv(SDL_Point point, const SDL_Surface* target, cpVect offset);

extern bool nullp(const void*);

extern void warn(const char*, const char*);

extern void crash(const char*, const char*);

extern int ran_domo(Uint32 min, Uint32 max);

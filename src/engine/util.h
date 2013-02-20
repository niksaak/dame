#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include <SDL/SDL.h>
#include <chipmunk/chipmunk.h>

#ifdef DEBUG_MODE
#include <stdio.h>
#define DEBUG(...) \
  fprintf(stderr, __VA_ARGS__);
#else
#define DEBUG(...)
#endif

#define WARN(...) \
  promulgate(__func__, false, __VA_ARGS__);

#define CRASH(...) \
  promulgate(__func__, true, __VA_ARGS__);

typedef struct SDL_point {
  int x;
  int y;
} SDL_Point;

extern SDL_Point SDLpt(int x, int y);

extern SDL_Point cpvSDL(cpVect vector, const SDL_Surface* target, cpVect offset);

extern cpVect SDLcpv(SDL_Point point, const SDL_Surface* target, cpVect offset);

extern bool nullp(const void*);

extern void
promulgate(const char* funname, bool crushing, const char* warning, ...);

extern void warn(const char*, const char*);

extern void crash(const char*, const char*);

extern int ran_domo(Uint32 min, Uint32 max);

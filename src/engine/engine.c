#include <stdbool.h>
#include <assert.h>

#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <chipmunk/chipmunk.h>

#include "engine.h"

static bool running = true;
static Uint32 phycount = 0;
static Uint32 gfxcount = 0;
static Uint32 timcount = 0;

static void render(SDL_Surface* screen, void (*renderf)())
{
  void benchprint()
  {
    static char phstr[64] = {0};
    static char gxstr[64] = {0};

    if(timcount > 1000) {
      snprintf(phstr, 64, "PHY FPS: %u", phycount);
      snprintf(gxstr, 64, "GFX FPS: %u", gfxcount);
      phycount = 0;
      gfxcount = 0;
      timcount = 0;
    }

    stringColor(screen, 10, screen->h - 20, phstr, 0xffffffff);
    stringColor(screen, 10, screen->h - 10, gxstr, 0xffffffff);
  }

  SDL_FillRect(screen, NULL, 0);
  (*renderf)();
  benchprint();
  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void gameloop(SDL_Surface* screen)
{
  assert(!nullp(screen));

  Uint32 dt = 10;
  Uint32 curt = SDL_GetTicks();
  Uint32 accum = 0;

  while(running) {
    Uint32 newt;
    Uint32 framet;
    state_t* st;

    ++gfxcount;
    st = curstate();
    newt = SDL_GetTicks();
    framet = newt - curt;
    curt = newt;
    accum += framet;

    while(accum >= dt) {
      ++phycount;
      st->do_world(dt / 1000.0);
      accum -= dt;
    }

    render(screen, st->do_render);
    
    if(st != curstate()) {
      st->sleep();
      curstate()->wake();
    }
    timcount += framet;
  }
}

void endgame()
{
  running = false;
}

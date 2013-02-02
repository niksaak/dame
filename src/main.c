#include <stdio.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "engine/system.h"
#include "engine/util.h"
#include "engine/stateman.h"
#include "states.h"
#include "main.h"

bool running = true;
Uint32 run_counter = 9001;

int timcount = 0;
int phycount = 0;
int gfxcount = 0;

void benchprint()
{
  SDL_Surface* win = NULL;
  static char phstr[64] = {0};
  static char gxstr[64] = {0};

  if((win = scrget()) == NULL)
    CRASH(SDL_GetError());
  if(timcount > 1000) {
    snprintf(phstr, 64, "PHY FPS: %i", phycount);
    snprintf(gxstr, 64, "GFX FPS: %i", gfxcount);
    timcount = 0;
    phycount = 0;
    gfxcount = 0;
  }
  stringColor(win, 10, win->h - 20, phstr, 0xffffffff);
  stringColor(win, 10, win->h - 10, gxstr, 0xffffffff);
}

int main(int argc, char** argv)
{
  state_t state; // main state IGNOT
  Uint32 dt = 10; // gameloop vars
  Uint32 curtime = 0;
  Sint32 accum = 0;

  state = state_main(); // TODO: move this to init_states() or something

  scrstart("TEST", 512, 512, false); // window appearifies here
  state.init(); // init our main-and-only (MANLY) gamestate
  swstate(&state);
  curtime = SDL_GetTicks(); // initial timerset

  while(run_counter) {
    Uint32 newtime; // local gameloop vars
    Uint32 frametime;
    state_t* st;

    st = curstate();
    newtime = SDL_GetTicks(); // getting time for frame
    frametime = newtime - curtime;
    curtime = newtime;

    accum += frametime;

    while(accum >= dt) { // physics loop
      st->do_world(dt / 1000.0);
      accum -= dt;
      ++phycount;
    }

    SDL_FillRect(scrget(), NULL, 0); // rendering
    st->do_render();
    benchprint();
    SDL_UpdateRect(scrget(), 0, 0, 0, 0);

    if(st != curstate()) { // put state to sleep if it in not current anymore
      st->sleep();
      curstate()->wake();
    }
    ++gfxcount;
    --run_counter;
    timcount += frametime;
  }
  state.deinit();

  scrstop();

  return 0;
}

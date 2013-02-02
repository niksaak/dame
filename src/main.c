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

  if((win = get_screen()) == NULL)
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
  state_t state;
  Uint32 t = 0;
  Uint32 dt = 10;
  Uint32 curtime = 0;
  Sint32 accum = 0;

  state = state_main();

  start_screen("TEST", 512, 512, false);
  state.init();
  switch_state(&state);
  curtime = SDL_GetTicks();

  while(run_counter) {
    Uint32 newtime;
    Uint32 frametime;
    state_t* st;

    st = CurrentState;
    newtime = SDL_GetTicks();
    frametime = newtime - curtime;
    curtime = newtime;

    accum += frametime;

    while(accum >= dt) {
      st->do_world(dt / 1000.0);
      accum -= dt;
      t += dt;
      ++phycount;
    }

    SDL_FillRect(get_screen(), NULL, 0);
    st->do_render();
    benchprint();
    SDL_UpdateRect(get_screen(), 0, 0, 0, 0);

    if(st != CurrentState) {
      st->sleep();
      CurrentState->wake();
    }
    ++gfxcount;
    --run_counter;
    timcount += frametime;
  }
  state.deinit();

  stop_screen();

  return 0;
}

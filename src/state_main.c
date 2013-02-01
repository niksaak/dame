#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "engine/system.h"
#include "states.h"

static void init()
{ }

static void wake()
{ }

static void do_world(cpFloat step)
{ }

static void do_render()
{
  SDL_Surface* screen;

  screen = get_screen();
  SDL_FillRect(screen, NULL, 0);
  stringColor(screen, 20, 20, "Hello world", 0xffffffff);
  SDL_UpdateRect(screen, 0, 0, 0, 0);
}

static void sleep()
{ }

static void deinit()
{ }

state_t state_main()
{
  state_t s;

  s.init = &init;
  s.wake = &wake;
  s.do_world = &do_world;
  s.do_render = &do_render;
  s.sleep = &sleep;
  s.deinit = &deinit;

  return s;
}


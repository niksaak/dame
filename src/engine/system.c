#include <stdbool.h>
#include <SDL/SDL.h>

#include "system.h"
#include "util.h"

static bool ScreenOn = false;
static bool UsingOGL = false;

void start_screen(const char* title, int width, int height, bool ogl)
{
  SDL_Surface* screen = NULL;
  Uint32 scrflags;

  if(ogl) {
    scrflags = SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF;
    UsingOGL = true;
  } else
    scrflags = SDL_SWSURFACE;

  if(ScreenOn)
    CRASH("Screen is on already");

  printf("Initializing SDL.\n");
  DEBUG("   doing SDL_Init()...\n");
  if(SDL_Init(INITFLAGS) != 0) {
    CRASH(SDL_GetError());
  }
  DEBUG("   setting video mode to %ix%i, %ibpp...\n", width, height, 32);
  if(nullp(SDL_SetVideoMode(width, height, 32, scrflags)))
    CRASH(SDL_GetError());
  DEBUG("   setting clip rectangle...\n");
  SDL_SetClipRect(screen, NULL);
  DEBUG("   setting caption to \"%s\"...\n", title);
  SDL_WM_SetCaption(title, title);
  DEBUG("   enabling key repeat...\n");
  SDL_EnableKeyRepeat
    (SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);
  screen = SDL_GetVideoSurface();
  printf("OK: %ix%i, %ibpp\n",
      screen->w, screen->h, screen->format->BitsPerPixel);
  ScreenOn = true;
}

void stop_screen()
{
  if(!ScreenOn) {
    WARN("Attempt to deinit screen whilst it was not initialized");
  } else {
    printf("Deinitializing SDL.\n");
    SDL_Quit();
  }
}

SDL_Surface* get_screen()
{
  if(!ScreenOn)
    return NULL;
  return SDL_GetVideoSurface();
}

bool screen_on()
{
  return ScreenOn;
}

bool using_ogl()
{
  return UsingOGL;
}

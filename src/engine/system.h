#pragma once

#ifndef INITFLAGS
#define INITFLAGS SDL_INIT_EVERYTHING
#endif

extern void start_screen(const char* title, int width, int height, bool ogl);
extern void stop_screen();
extern SDL_Surface* get_screen();
extern bool screen_on();
extern bool using_ogl();

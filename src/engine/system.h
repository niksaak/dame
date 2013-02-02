#pragma once

#ifndef INITFLAGS
#define INITFLAGS SDL_INIT_EVERYTHING
#endif

extern void scrstart(const char* title, int width, int height, bool ogl);

extern void scrstop();

extern SDL_Surface* scrget();

extern bool scronp();

extern bool using_ogl_p();


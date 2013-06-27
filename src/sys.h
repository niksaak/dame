#pragma once

int running;

int setup_gfx(const char* title, int width, int height);
  // do necessary preparations and initializations

int stop_gfx(void);
  // deinitialize graphics

int keypress(int key);
  // returns nonzero if key is pressed

int wait(double ms);
  // wait for some miliseconds

int render(void);
  // render and swap buffers

double zoom(double factor);
  // set zoom factor and return it, or just return it if 'factor' is zero


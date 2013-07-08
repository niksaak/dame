#pragma once

/* SYS
 * system utilities
 */

#include <chipmunk/chipmunk.h>

int running;


/* Graphics setup */

int start_gfx(const char* title, int width, int height);
  // do necessary preparations and initializations

int stop_gfx(void);
  // deinitialize graphics


/* Events */

int keypress(int key);
  // returns nonzero if key is pressed

int wait(double ms);
  // wait for some miliseconds


/* Rendering */

int render(void);
  // render and swap buffers

double zoom(double factor);
  // set zoom if `factor` is not zero and return it


/* Physics */

cpSpace* init_space(void);

cpSpace* current_space(void);

int deinit_space(void);

int remove_body(cpBody* body, cpSpace* space);
  // remove body and all its shapes from space and then free them


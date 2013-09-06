#pragma once

/* SYS
 * system utilities
 */

#include <chipmunk/chipmunk.h>

int running; // FIXME: get rid of this

/* Events */

int keypress(int key);
  // returns nonzero if key is pressed

int wait(double ms);
  // wait for some miliseconds



/* Physics */

cpSpace* init_space(void);

cpSpace* current_space(void);

int deinit_space(void);

int remove_body(cpBody* body);
  // remove body and all its shapes from space and then free them


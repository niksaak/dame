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


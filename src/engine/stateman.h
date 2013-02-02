#pragma once

#include <chipmunk/chipmunk.h>

typedef struct state {
  void (*init)();

  void (*wake)();

  void (*do_world)(cpFloat);
  void (*do_render)();

  void (*sleep)();

  void (*deinit)();
} state_t;

extern state_t* curstate();

extern void swstate(state_t* other_state);


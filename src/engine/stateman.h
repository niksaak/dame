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

extern state_t* CurrentState;

extern state_t* get_current_state();

extern void switch_state(state_t* other_state);


#pragma once

#include <chipmunk/chipmunk.h>

#define STATE_ENTRY_NAME_LEN 64

typedef struct state {
  void (*init)();

  void (*wake)();

  void (*do_world)(cpFloat);
  void (*do_render)();

  void (*sleep)();

  void (*deinit)();
} state_t;

extern void register_state(const char* name, state_t* state);

extern void init_states(void);

extern void deinit_states(void);

extern void clear_registry(void);

extern state_t* curstate(void);

extern void swstate(const char* name);


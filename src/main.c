#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>

#include "engine/system.h"
#include "engine/util.h"
#include "engine/stateman.h"
#include "states.h"
#include "main.h"

int main(int argc, char** argv)
{
  printf("Hello World!\n");
  state_t state;

  state = state_main();
  start_screen("TEST", 512, 512, false);
  state.wake();
  state.do_world();
  state.do_render();
  state.sleep();
  state.deinit();
  stop_screen();

  return 0;
}

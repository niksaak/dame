#include "engine/engine.h"
#include "states.h"
#include "main.h"

int main(int argc, char** argv)
{
  state_t state; // main state IGNOT

  state = state_main(); // TODO: move this to init_states() or something

  state.init(); // init our main-and-only (MANLY) gamestate
  swstate(&state);

  scrstart("TEST", 512, 512, false); // window appearifies here
  gameloop(scrget());
  scrstop();

  state.deinit();

  return 0;
}

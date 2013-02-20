#ifdef _WIN32
#include <windows.h>
#endif

#include "engine/engine.h"
#include "state_main.h"
#include "main.h"

int main(int argc, char** argv)
{
  register_state("main", state_main());
  init_states();
  
  swstate("main");

  scrstart("TEST", 512, 512, false); // window appearifies here
  gameloop(scrget());
  scrstop();

  deinit_states();
  clear_registry();

  return 0;
}

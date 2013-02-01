#include <stdbool.h>

#include "stateman.h"
#include "util.h"

state_t* CurrentState = NULL;

state_t* get_current_state()
{
  return &CurrentState;
}

void switch_state(state_t* state)
{
  CurrentState = state;
}


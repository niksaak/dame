#include <stdbool.h>

#include "stateman.h"
#include "util.h"

state_t* CurrentState = NULL;

state_t* curstate()
{
  return CurrentState;
}

void swstate(state_t* state)
{
  CurrentState = state;
}


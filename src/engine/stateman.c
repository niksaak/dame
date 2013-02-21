#include <stdbool.h>

#include "stateman.h"
#include "util.h"

typedef struct state_entry_t {
  const char* name;
  state_t* state;
} state_entry_t;

typedef struct states_list_t {
  state_entry_t node;
  struct states_list_t* next;
} states_list_t;

states_list_t* StatesRegistry = NULL;
state_t* CurrentState = NULL;

static states_list_t* statecons(state_entry_t node, states_list_t* list)
{
  states_list_t* cons = malloc(sizeof(states_list_t));
  cons->node = node;
  cons->next = list;

  return cons;
}

static state_t* find_state(const char* name)
{
  state_t* find(states_list_t* list)
  {
    if(nullp(list)) {
      return NULL;
    } else if(!strcmp(name, list->node.name)) {
      return list->node.state;
    } else {
      return find(list->next);
    }
  }

  return find(StatesRegistry);
}

void register_state(const char* name, state_t* state)
{
  state_entry_t node = {name, state};
  states_list_t* cons = statecons(node, StatesRegistry);

  if(!nullp(find_state(name)))
    CRASH("Trying to register state that already exitst: %s");
  StatesRegistry = cons;
}

void init_states(void)
{
  for(const states_list_t* list = StatesRegistry;
      !nullp(list); list = list->next)
  {
    list->node.state->init();
  }
}

void deinit_states(void)
{
  for(const states_list_t* list = StatesRegistry; 
      !nullp(list); list = list->next)
  {
    list->node.state->deinit();
  }
}

void clear_registry(void)
{
  int destroy(states_list_t* list)
  {
    if(nullp(list))
      return 0;

    states_list_t* next = list->next;
    
    free(list);
    return destroy(next);
  }

  destroy(StatesRegistry);
}

state_t* curstate(void)
{
  return CurrentState;
}

void swstate(const char* name)
{
  state_t* new_state = find_state(name);
  
  if(nullp(new_state))
    CRASH("Can not switch to state %s because it does not exist", name);
  if(!nullp(CurrentState))
    CurrentState->sleep();
  new_state->wake();
  CurrentState = new_state;
}

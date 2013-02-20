#include <assert.h>

#include "procman.h"
#include "util.h"

Process* mkproclist(void)
{
  Process* proc = malloc(sizeof(Process));

  proc->name = NULL;
  proc->func = NULL;
  proc->next = NULL;

  return proc;
}

Process*
procpush(const char* name, ProcessFunction func, void* data, Process* list)
{
  assert(!nullp(list));

  if(nullp(list->name) && nullp(list->func) && nullp(list->data)) {
    list->name = name;
    list->func = func;
    list->data = data;
    return list;
  } else if(nullp(list->next)) {
    list->next = mkproclist();
  }

  return procpush(name, func, data, list->next);
}

bool procpop(const char* name, Process* list)
{
  int process_pop(Process* list, Process* prev)
  {
    if(!strcmp(list->name, name)) {
      if(nullp(list->next)) {
        prev->next = NULL;
        free(list);
      } else if(nullp(prev)) {
        list->name = list->next->name;
        list->func = list->next->func;
        list->next = list->next->next;
        free(list->next);
      } else {
        prev->next = list->next;
        free(list);
      }
      return true;
    } else if(nullp(list->next)) {
      WARN("Unable to find process");
      return false;
    } else
      return process_pop(list->next, list);
  }

  return process_pop(list, NULL);
}

void delproclist(Process* list)
{
  if(!nullp(list->next))
    delproclist(list->next);
  free(list);
}

void procdo(Process* list)
{
  assert(!nullp(list));

  for(Process* cons = list; !nullp(cons); list = cons = cons->next)
    list->func(list->data);
}


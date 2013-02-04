#pragma once

#include <stdbool.h>

typedef void (*ProcessFunction)(void* data);

typedef struct Process {
  const char* name;
  ProcessFunction func;
  void* data;
  struct Process* next;
} Process;

extern Process* mkproclist(void);

extern void delproclist(Process* list);

extern Process*
procpush(const char* name, ProcessFunction func, void* data, Process* list);

extern bool procpop(const char* name, Process* list);

extern void procdo(Process* list);

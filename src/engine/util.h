#pragma once

#ifdef DEBUG_MODE
#include <stdio.h>
#define DEBUG(...) \
  fprintf(stderr, __VA_ARGS__);
#endif

#define WARN(w) \
  warn(__func__, w);

#define CRASH(r) \
  crash(__func__, r);

extern bool nullp(const void*);
extern void warn(const char*, const char*);
extern void crash(const char*, const char*);

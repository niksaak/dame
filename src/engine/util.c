#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "util.h"

bool nullp(const void* ptr)
{
  if(ptr == NULL)
    return true;
  return false;
}

void warn(const char* funname, const char* warning)
{
  fprintf(stderr, "%s: WARNING: %s\n", funname, warning);
}

void crash(const char* funname, const char* reason)
{
  if(nullp(reason))
    reason = strerror(errno);
  fprintf(stderr, "%s: CRUSHING ERROR: %s\n", funname, reason);
  exit(EXIT_FAILURE);
}

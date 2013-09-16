#include "error.h"

#include <stdio.h>
#include "util.h"

static const char* statusstr[] = {
  "PANIC",
  "ERROR",
  "WARNING",
  "MESSAGE",
  "UNKNOWN"
};

static const size_t statusstrc = ARRLEN(statusstr, const char*);

void error(int status, const char* fmt, ...)
{
  va_list ap;

  if(status >= statusstrc) {
    status = statusstrc - 1;
  }
  fprintf(stderr, "%7s: ", statusstr[status]);
  va_start(ap, fmt);
  {
    vfprintf(stderr, fmt, ap);
  }
  va_end(ap);
  fputc('\n', stderr);

  if(status == PANIC) {
    abort();
  }
}


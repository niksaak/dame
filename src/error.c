#include "error.h"

#include <stdio.h>
#include "util.h"

static const char* statusstr[] = {
  "PANIC",
  "ERROR",
  "WARNING",
  "MESSAGE",
  "DEBUG",
  "UNKNOWN"
};

static const size_t statusstrc = ARRLEN(statusstr, const char*);

void _eprintf(enum error_status status, const char* file, int line,
              const char* func, const char* fmt, ...)
{
  va_list ap;

  if(status >= statusstrc || status < EPANIC) {
    status = statusstrc - 1;
  }

#ifndef NDEBUG
  fprintf(stderr, "%s:%i:%s():\n", file, line, func); // print file and line info
#else
  fprintf(stderr, "@%s() ", func);
#endif

  fprintf(stderr, "%7s: ", statusstr[status]);
  va_start(ap, fmt);
  {
    vfprintf(stderr, fmt, ap);
  }
  va_end(ap);
  fputc('\n', stderr);

  if(status == EPANIC) {
    abort();
  }
}


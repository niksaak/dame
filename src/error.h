#pragma once

#include <stdio.h>

enum error_status {
  EPANIC   = 0,
  EERROR   = 1,
  EWARNING = 2,
  EMESSAGE = 3,
  EDEBUG   = 4
};

#define eprintf(status, fmt, ...) \
  _eprintf(status, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#ifndef NDEBUG
#define debug(fmt, ...) eprintf(EDEBUG, fmt, ##__VA_ARGS__)
#else
#define debug(fmt, ...) (void)0
#endif

#define message(fmt, ...) eprintf(EMESSAGE, fmt, ##__VA_ARGS__)

#define warning(fmt, ...) eprintf(EWARNING, fmt, ##__VA_ARGS__)

#define error(fmt, ...) eprintf(EERROR, fmt, ##__VA_ARGS__)

#define panic(fmt, ...) eprintf(EPANIC, fmt, ##__VA_ARGS__)

void _eprintf(enum error_status status,
              const char* file,
              int line,
              const char* func,
              const char* fmt,
              ...)
  __attribute__((format(printf, 5, 6)));


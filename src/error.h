#pragma once

#include <stdio.h>

enum error_status {
  EPANIC   = 0,
  EERROR   = 1,
  EWARNING = 2,
  EMESSAGE = 3
};

#define _error_helper(status, fmt, ...) \
  _error(status, __FILE__, __LINE__, __func__, fmt, ##__VA_ARGS__)

#define message(fmt, ...) _error_helper(EMESSAGE, fmt, ##__VA_ARGS__)

#define warning(fmt, ...) _error_helper(EWARNING, fmt, ##__VA_ARGS__)

#define error(fmt, ...) _error_helper(EERROR, fmt, ##__VA_ARGS__)

#define panic(fmt, ...) _error_helper(EPANIC, fmt, ##__VA_ARGS__)

void _error(enum error_status status,
            const char* file,
            int line,
            const char* func,
            const char* fmt,
            ...)
  __attribute__((format(printf, 5, 6)));


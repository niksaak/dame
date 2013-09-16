#pragma once

#include <stdio.h>

typedef enum ErrorStatus {
  PANIC   = 0,
  ERROR   = 1,
  WARNING = 2,
  MESSAGE = 3
} ErrorStatus;

void error(int status, const char* fmt, ...)
  __attribute__((format(printf, 2, 3)));


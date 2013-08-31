#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Handmaid unittest framework
 *
 * API short:
 * struct Tester - structure with data necessary for performing tests
 * START_DEFTEST(name) - start test definition
 * END_DEFTEST - end test definition
 * TASSERT(assertion) - fallthrough assert
 * TEASSERT(assertion) - no fallthrough assert
 * FAIL(msg) - fail immediately with custom message
 * TEST(name, tester) - run test named name with tester
 * print_test_summary(runner) - print summary for tests ran with runner
 */

typedef struct Tester {
  const char* name;         // name for runner

  const char* test;         // name of the current test
  bool fail;                // true if the test has failed

  int testc;                // test count
  int passc;                // passed test count
  int failc;                // failed test count
} Tester;

#define START_DEFTEST(test_name)           \
  static void test_name(Tester* _tester)   \
  {                                        \
    _tester->test = __func__;              \
    _tester->testc++;                      \
    TEASSERT(_tester != NULL);             \
    _tester->fail = false;

#define END_DEFTEST     \
  ret:                  \
    if(_tester->fail) { \
      _tester->failc++; \
    } else {            \
      _tester->passc++; \
    }                   \
  }

#define TASSERT(a)                                                \
  do {                                                            \
    if(!(a)) {                                                    \
      _tester->fail = true;                                       \
      fprintf(stderr, "%s @ %s\n %s failed.\n",                   \
              _tester->test, _tester->name, #a);                  \
    }                                                             \
  } while(0)

#define TEASSERT(a)                                               \
  do {                                                            \
    if(!(a)) {                                                    \
      _tester->fail = true;                                       \
      fprintf(stderr, "%s @ %s\n %s failed.\n",                   \
              _tester->test, _tester->name, #a);                  \
      goto ret;                                                   \
    }                                                             \
  } while(0)

#define TASSERTM(a, fmt, ...)                                     \
  do {                                                            \
    if(!(a)) {                                                    \
      _tester->fail = true;                                       \
      fprintf(stderr, "%s @ %s\n %s failed: ",                    \
              _tester->test, _tester->name, #a);                  \
      fprintf(stderr, fmt, __VA_ARGS__);                          \
      fputc('\n', stderr);                                        \
    }                                                             \
  } while(0)

#define TEASSERTM(a, fmt, ...)                                    \
  do {                                                            \
    if(!(a)) {                                                    \
      tester->fail = true;                                        \
      fprintf(stderr, "%s @ %s\n %s failed: ",                    \
              _tester->test, _tester->name, #a);                  \
      fprintf(stderr, fmt, __VA_ARGS__);                          \
      fputc('\n', stderr);                                        \
      goto ret;                                                   \
    }                                                             \
  } while(0)

#define FAIL(fmt, ...)                      \
  do {                                      \
    _tester->fail = true;                   \
    fprintf(stderr, "%s @ %s failed: ",     \
            _tester->test, _tester->name);  \
    fprintf(stderr, fmt, ##__VA_ARGS__);    \
    fputc('\n', stderr);                    \
    goto ret;                               \
  } while(0);

#define TEST(name, tester)    \
  name(_Generic((tester),     \
           Tester: &(tester), \
           Tester*: (tester), \
           void*: (tester)))

static inline void print_test_summary(const Tester r)
{
  printf("%s: %i total, %i passed, %i failed.\n",
         r.name, r.testc, r.passc, r.failc);
}


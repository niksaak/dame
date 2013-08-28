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
  const char* assertion;    // name of the current assertion
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
    _tester->assertion = NULL;             \
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
    _tester->assertion = #a;                                      \
    if(!(a)) {                                                    \
      _tester->fail = true;                                       \
      fprintf(stderr, "%s@%s: assertion (%s) failed\n",           \
              _tester->test, _tester->name, _tester->assertion);  \
    }                                                             \
  } while(0)

#define TEASSERT(a)                                               \
  do {                                                            \
    _tester->assertion = #a;                                      \
    if(!(a)) {                                                    \
      _tester->fail = true;                                       \
      fprintf(stderr, "%s@%s: assertion (%s) failed\n",           \
              _tester->test, _tester->name, _tester->assertion);  \
      goto ret;                                                   \
    }                                                             \
  } while(0)

#define TASSERTM(a, fmt, ...)                                     \
  do {                                                            \
    _tester->assertion = #a;                                      \
    if(!(a)) {                                                    \
      _tester->fail = true;                                       \
      fprintf(stderr, "%s@%s: assertion (%s) failed\n",           \
              _tester->test, _tester->name, _tester->assertion);  \
      fputs("    ", stderr);                                      \
      fprintf(stderr, fmt, __VA_ARGS__);                          \
      fputc('\n', stderr);                                        \
    }                                                             \
  } while(0)

#define TEASSERTM(a, fmt, ...)                                    \
  do {                                                            \
    _tester->assertion = #a;                                      \
    if(!(a)) {                                                    \
      tester->fail = true;                                        \
      fprintf(stderr, "%s@%s: assertion (%s) failed:\n",          \
              _tester->test, _tester->name, _tester->assertion);  \
      fputs("    ", stderr);                                      \
      fprintf(stderr, fmt, __VA_ARGS__);                          \
      fputc('\n', stderr);                                        \
      goto ret;                                                   \
    }                                                             \
  } while(0)

#define FAIL(fmt, ...)                      \
  do {                                      \
    _tester->assertion = NULL;              \
    _tester->fail = true;                   \
    fprintf(stderr, "%s@%s: failed - ",     \
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


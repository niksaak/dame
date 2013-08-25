#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Handmaid unittest framework
 *
 * API short:
 * struct Tester - structure with data necessary for performing tests
 * START_DEFTEST(name) - start test definition
 * END_DEFTEST - end test definition
 * TASSERT(assertion) - check assertion
 * TEST(name, tester) - run test named name with tester
 * print_test_summary(runner) - print summary for tests ran with runner
 */

typedef struct Tester {
  const char* name;  // name for runner

  const char* test;         // name of the current test
  const char* assertion;    // name of the current assertion
  bool fail;                // true if the test is failed

  int testc;                // test count
  int passc;                // passed test count
  int failc;                // failed test count
} Tester;

#define START_DEFTEST(test_name)  \
  void test_name(Tester* _tester) { \
    if(_tester == NULL) { \
      fprintf(stderr, "Fatal error: tester is NULL\n"); \
      exit(EXIT_FAILURE); \
    } \
    _tester->test = __func__; \
    _tester->assertion = NULL;  \
    _tester->fail = false;  \
    _tester->testc++;

#define END_DEFTEST \
    if(_tester->fail) { \
      _tester->failc++; \
    } else {  \
      _tester->passc++; \
    } \
  }

#define TASSERT(a)  \
  do {  \
    _tester->assertion = #a;  \
    if(!(a)) {  \
      _tester->fail = true; \
      fprintf(stderr, "%s: assertion (%s) failed\n",  \
              _tester->name, _tester->assertion); \
    } \
  } while(0)

#define TEST(name, tester) name(&tester);

static inline void print_test_summary(const Tester r)
{
  printf("\n%s:\n%3i total,\n%3i passed,\n%3i failed.\n",
         r.name, r.testc, r.passc, r.failc);
}


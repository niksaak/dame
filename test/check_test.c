#include "test.h"

START_DEFTEST(passer)
{
  TASSERT(0 == 0);
}
END_DEFTEST

START_DEFTEST(failer)
{
  TASSERT(1 == 9);
}
END_DEFTEST

Tester check_test(void)
{
  Tester r = {"check_test"};

  TEST(passer, r);
  TEST(failer, r);

  return r;
}


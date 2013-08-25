#include "test.h"

Tester check_test(void);

int main(int argc, char* argv[])
{
  Tester t_check_test = check_test();

  print_test_summary(t_check_test);

  return 0;
}


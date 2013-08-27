#include "test.h"

Tester check_test(void);
Tester check_draw(void);
Tester check_module(void);

int main(int argc, char* argv[])
{
  Tester draw_test = check_draw();
  Tester module_test = check_module();

  print_test_summary(draw_test);
  print_test_summary(module_test);

  return 0;
}


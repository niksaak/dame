#include "test.h"

Tester check_draw(void);
Tester check_module(void);
Tester check_particle(void);
Tester check_sys(void);
Tester check_entity(void);

int main(int argc, char* argv[])
{
  Tester tests[] = {
    check_draw(),
    check_module(),
    check_particle(),
    check_sys(),
    check_entity()
  };
  size_t tests_len = sizeof(tests) / sizeof(Tester);

  fputc('\n', stderr);
  for(int i = 0; i < tests_len; i++) {
    print_test_summary(tests[i]);
  }

  return 0;
}


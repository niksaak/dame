#include <check.h>
#include <signal.h>
#include "../src/error.h"

START_TEST(error_status_panic_signals_abort)
{
  message("Message test.");
  warning("Warning test.");
  error("Error test.");
  panic("Panic test, should abort now.");
}
END_TEST

Suite* mk_error_suite(void)
{
  Suite* s = suite_create("error");
  TCase* terr = tcase_create("error");

  tcase_add_test_raise_signal(terr, error_status_panic_signals_abort, SIGABRT);

  suite_add_tcase(s, terr);

  return s;
}


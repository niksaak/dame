#include <check.h>
#include "../src/sys.h"

/* space */

START_TEST(init_space_returns_current_space)
{
  cpSpace* s = init_space();

  ck_assert_ptr_ne(s, NULL);
  ck_assert_ptr_ne(current_space, NULL);
  ck_assert_ptr_eq(s, current_space());

  deinit_space();
}
END_TEST

START_TEST(remove_body_works)
{
  cpSpace* s = init_space();
  cpBody* b = cpSpaceAddBody(s, cpBodyNew(1, 1));
  cpShape* sh = cpSpaceAddShape(s, cpCircleShapeNew(b, 1, cpvzero));
  remove_body(b);

  ck_assert_ptr_ne(s, NULL);
  ck_assert_ptr_ne(b, NULL);
  ck_assert_ptr_ne(sh, NULL);

  ck_assert(!cpSpaceContainsBody(s, b));
  ck_assert(!cpSpaceContainsShape(s, sh));

  deinit_space();
}
END_TEST

START_TEST(remove_body_null_returns_nonzero)
{
  ck_assert_int_ne(remove_body(NULL), 0);
}
END_TEST

Suite* mk_sys_suite(void)
{
  Suite* s = suite_create("sys");
  TCase* tspace = tcase_create("space");

  tcase_add_test(tspace, init_space_returns_current_space);
  tcase_add_test(tspace, remove_body_works);
  tcase_add_test(tspace, remove_body_null_returns_nonzero);

  suite_add_tcase(s, tspace);

  return s;
}


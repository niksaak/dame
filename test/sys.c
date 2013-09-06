#include <check.h>
#include "../src/sys.h"

/* TODO: move gfx tests to draw
START_TEST(start_gfx_zero_dimensions_returns_nonzero)
{
  ck_assert_int_ne(start_gfx("test", 0, 0), 0);
  stop_gfx();
}
END_TEST

START_TEST(start_gfx_title_null_sets_default_title)
{
  ck_abort_msg("TODO"); // TODO
}
END_TEST

START_TEST(setzoom_returns_previous_zoom)
{
  double z0;
  double z1 = 0.5;
  double z2 = 1;
  double z3;

  z0 = setzoom(z1);
  z3 = setzoom(z2);

  ck_assert_msg(z3 == z1, "z3 == %g", z3);

  setzoom(z0);
}
END_TEST
*/

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
  // TCase* tgfx = tcase_create("gfx"); TODO
  TCase* tspace = tcase_create("space");

  /*
  tcase_add_test(tgfx, start_gfx_zero_dimensions_returns_nonzero);
  tcase_add_test(tgfx, start_gfx_title_null_sets_default_title);
  tcase_add_test(tgfx, setzoom_returns_previous_zoom);
  */
  tcase_add_test(tspace, init_space_returns_current_space);
  tcase_add_test(tspace, remove_body_works);
  tcase_add_test(tspace, remove_body_null_returns_nonzero);
  // suite_add_tcase(s, tgfx);
  suite_add_tcase(s, tspace);

  return s;
}


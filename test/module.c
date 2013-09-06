#include <check.h>
#include "../src/module.h"
#include "../src/sys.h"
#include "../src/draw.h"

static void setup(void)
{
  init_space();
}

static void teardown(void)
{
  deinit_space();
}

START_TEST(mkmodule_pos)
{
  module_t* m = mkmodule((cpVect){ 9, -15 });
  cpVect pos;

  ck_assert_ptr_ne(m, NULL);
  ck_assert_ptr_ne(m->body, NULL);
  pos = cpBodyGetPos(m->body);
  ck_assert_msg(cpveql(pos, (cpVect){ 9, -15 }),
                "pos == (cpVect){ %g, %g }", pos.x, pos.y);
}
END_TEST

START_TEST(kmmodule_null_returns_nonzero)
{
  ck_assert_int_ne(kmmodule(NULL), 0);
}
END_TEST

START_TEST(punch_module_null_returns_nonzero)
{
  ck_assert_int_ne(punch_module(NULL, (cpVect){ 1, 1 }), 0);
}
END_TEST

START_TEST(draw_module_null_returns_nonzero)
{
  start_gfx("draw_module_null_returns_nonzero", 128, 128);

  ck_assert_int_ne(draw_module(NULL), 0);

  stop_gfx();
}
END_TEST

Suite* mk_module_suite(void)
{
  Suite* s = suite_create("module");
  TCase* tworld = tcase_create("world");
  TCase* tdraw = tcase_create("draw");

  tcase_add_checked_fixture(tworld, setup, teardown);
  tcase_add_test(tworld, mkmodule_pos);
  tcase_add_test(tworld, kmmodule_null_returns_nonzero);
  tcase_add_test(tworld, punch_module_null_returns_nonzero);
  tcase_add_test(tdraw, draw_module_null_returns_nonzero);

  suite_add_tcase(s, tworld);
  suite_add_tcase(s, tdraw);

  return s;
}


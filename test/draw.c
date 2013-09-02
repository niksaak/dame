#include <check.h>
#include "../src/draw.h"
#include "../src/sys.h"

static void setup(void)
{
  start_gfx("draw_null_test", 128, 128);
}

static void teardown(void)
{
  stop_gfx();
}

START_TEST(draw_points_null_returns_nonzero)
{
  ck_assert_int_ne(draw_points(NULL, 9), 0);
}
END_TEST

START_TEST(draw_polyline_null_returns_nonzero)
{
  ck_assert_int_ne(draw_points(NULL, 9), 0);
}
END_TEST

START_TEST(draw_polygon_null_returns_nonzero)
{
  ck_assert_int_ne(draw_polygon(NULL, 9), 0);
}
END_TEST

START_TEST(draw_curve_null_returns_nonzero)
{
  ck_assert_int_ne(draw_polygon(NULL, 9), 0);
}
END_TEST

Suite* mk_draw_suite(void)
{
  Suite* s = suite_create("draw");
  TCase* c = tcase_create("draw-NULL");

  tcase_add_checked_fixture(c, setup, teardown);
  tcase_add_test(c, draw_points_null_returns_nonzero);
  tcase_add_test(c, draw_polyline_null_returns_nonzero);
  tcase_add_test(c, draw_polygon_null_returns_nonzero);
  tcase_add_test(c, draw_curve_null_returns_nonzero);
  suite_add_tcase(s, c);

  return s;
}


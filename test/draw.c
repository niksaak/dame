#include <check.h>
#include "../src/draw.h"
#include "../src/sys.h"

/* gfx */

START_TEST(start_gfx_zero_dimensions_returns_nonzero)
{
  ck_assert_int_ne(start_gfx("test", 0, 0), 0);
  stop_gfx();
}
END_TEST

START_TEST(start_gfx_title_null_returns_nonzero)
{
  ck_assert_int_ne(start_gfx(NULL, 128, 128), 0);
  stop_gfx();
}
END_TEST

START_TEST(stop_gfx_not_started_returns_nonzero)
{
  ck_assert_int_ne(stop_gfx(), 0);
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

/* draw-NULL */

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
  TCase* tgfx = tcase_create("gfx");
  TCase* tdnu = tcase_create("draw-NULL");

  // gfx:
  tcase_add_test(tgfx, start_gfx_zero_dimensions_returns_nonzero);
  tcase_add_test(tgfx, start_gfx_title_null_returns_nonzero);
  tcase_add_test(tgfx, stop_gfx_not_started_returns_nonzero);
  tcase_add_test(tgfx, setzoom_returns_previous_zoom);

  // draw-NULL:
  tcase_add_checked_fixture(tdnu, setup, teardown);
  tcase_add_test(tdnu, draw_points_null_returns_nonzero);
  tcase_add_test(tdnu, draw_polyline_null_returns_nonzero);
  tcase_add_test(tdnu, draw_polygon_null_returns_nonzero);
  tcase_add_test(tdnu, draw_curve_null_returns_nonzero);

  suite_add_tcase(s, tgfx);
  suite_add_tcase(s, tdnu);

  return s;
}


#include "test.h"
#include "../src/draw.h"
#include "../src/sys.h"

START_DEFTEST(draw_null_returns_nonzero)
{
  start_gfx("draw_null_returns_nonzero", 128, 128);

  TASSERT(draw_points(NULL, 9) != 0);
  TASSERT(draw_polyline(NULL, 9) != 0);
  TASSERT(draw_polygon(NULL, 9) != 0);
  TASSERT(draw_curve(NULL, 9) != 0);

  stop_gfx();
}
END_DEFTEST

Tester check_draw(void)
{
  Tester t = {"draw"};

  TEST(draw_null_returns_nonzero, t);

  return t;
}

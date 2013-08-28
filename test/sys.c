#include "test.h"
#include "../src/sys.h"

START_DEFTEST(start_gfx_zero_dimensions_returns_nonzero)
{
  TASSERT(start_gfx("start_gfx_zero_dimensions_returns_nonzero", 0, 0) != 0);
  stop_gfx();
}
END_DEFTEST

START_DEFTEST(start_gfx_title_null_sets_default_title)
{
  FAIL("TODO"); // TODO
}
END_DEFTEST

START_DEFTEST(setzoom_returns_previous_zoom)
{
  double z0;
  double z1 = 0.5;
  double z2 = 1;
  double z3;

  z0 = setzoom(z1);
  z3 = setzoom(z2);

  TASSERTM(z3 == z1, "z3 == %g", z3);

  setzoom(z0);
}
END_DEFTEST

START_DEFTEST(init_space_returns_current_space)
{
  cpSpace* s = init_space();

  TASSERT(s != NULL);
  TASSERT(current_space != NULL);
  TASSERT(s == current_space());

  deinit_space();
}
END_DEFTEST

START_DEFTEST(remove_body_works)
{
  cpSpace* s = init_space();
  cpBody* b = cpSpaceAddBody(s, cpBodyNew(1, 1));
  cpShape* sh = cpSpaceAddShape(s, cpCircleShapeNew(b, 1, cpvzero));
  remove_body(b);

  TEASSERT(s != NULL);
  TEASSERT(b != NULL);
  TEASSERT(sh != NULL);

  TASSERT(!cpSpaceContainsBody(s, b));
  TASSERT(!cpSpaceContainsShape(s, sh));

  deinit_space();
}
END_DEFTEST

START_DEFTEST(remove_body_null_returns_nonzero)
{
  TASSERT(remove_body(NULL) != 0);
}
END_DEFTEST

Tester check_sys(void)
{
  Tester t = {"sys"};

  TEST(start_gfx_zero_dimensions_returns_nonzero, t);
  TEST(start_gfx_title_null_sets_default_title, t);
  TEST(setzoom_returns_previous_zoom, t);
  TEST(init_space_returns_current_space, t);
  TEST(remove_body_works, t);
  TEST(remove_body_null_returns_nonzero, t);

  return t;
}


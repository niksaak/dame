#include "test.h"
#include "../src/module.h"
#include "../src/sys.h"

START_DEFTEST(mkmodule_pos)
{
  init_space();

  module_t* m = mkmodule((cpVect){ 9, -15 });
  TEASSERT(m != NULL);
  TEASSERT(m->body != NULL);
  TASSERTM(cpveql(cpBodyGetPos(m->body), (cpVect){ 9, -15 }),
           "pos == %s", cpvstr(cpBodyGetPos(m->body)));

  deinit_space();
}
END_DEFTEST

START_DEFTEST(kmmodule_null_returns_nonzero)
{
  init_space();

  TASSERT(kmmodule(NULL) != 0);

  deinit_space();
}
END_DEFTEST

START_DEFTEST(draw_module_null_returns_nonzero)
{
  start_gfx("draw_module_null_returns_nonzero", 128, 128);

  TASSERT(draw_module(NULL) != 0);

  stop_gfx();
}
END_DEFTEST

START_DEFTEST(punch_module_null_returns_nonzero)
{
  init_space();

  TASSERT(punch_module(NULL, (cpVect){1, 1}) != 0);

  deinit_space();
}
END_DEFTEST

Tester check_module(void) {
  Tester t = {"module"};

  TEST(mkmodule_pos, t);
  TEST(kmmodule_null_returns_nonzero, t);
  TEST(draw_module_null_returns_nonzero, t);
  TEST(punch_module_null_returns_nonzero, t);

  return t;
}


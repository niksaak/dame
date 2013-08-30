#include "test.h"
#include "../src/particle.h"
#include "../src/sys.h"

START_DEFTEST(mkparticle_does_the_job)
{
  init_space();

  int id = mkparticle(HOT_PARTICLE, cpvzero, (cpVect){ 0.1, -0.1 }, 1000);
  particle_t* p = particle(id);
  TEASSERT(p != NULL);
  TEASSERT(p->body != NULL);
  TASSERT(cpveql(cpBodyGetPos(p->body), cpvzero));
  TASSERT(cpveql(cpBodyGetVel(p->body), (cpVect){ 0.1, -0.1 }));
  TASSERT(p->energy == 1000);

  deinit_space();
}
END_DEFTEST

START_DEFTEST(kmparticle_id_unknown_returns_nonzero)
{
  init_space();

  TASSERT(kmparticle(-1) != 0);

  deinit_space();
}
END_DEFTEST

START_DEFTEST(kmparticle_ptr_null_returns_nonzero)
{
  init_space();

  TASSERT(kmparticle(NULL) != 0);

  deinit_space();
}
END_DEFTEST

Tester check_particle(void)
{
  Tester t = {"particle"};

  TEST(mkparticle_does_the_job, t);
  TEST(kmparticle_id_unknown_returns_nonzero, t);
  TEST(kmparticle_ptr_null_returns_nonzero, t);

  return t;
}

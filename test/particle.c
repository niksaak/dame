#include <check.h>
#include "../src/particle.h"
#include "../src/entity.h"

static void setup(void)
{
  init_space();
}

static void teardown(void)
{
  deinit_space();
}

START_TEST(mkparticle_works)
{
  int id = mkparticle(HOT_PARTICLE, cpvzero, (cpVect){ 0.1, -0.1 }, 1000);
  particle_t* p = particle(id);

  ck_assert_ptr_ne(p, NULL);
  ck_assert_ptr_ne(p->body, NULL);
  ck_assert(cpveql(cpBodyGetPos(p->body), cpvzero));
  ck_assert(cpveql(cpBodyGetVel(p->body), (cpVect){ 0.1, -0.1 }));
  ck_assert(p->energy == 1000);
}
END_TEST

START_TEST(kmparticle_id_unknown_returns_nonzero)
{
  ck_assert_int_ne(kmparticle(-1), 0);
}
END_TEST

START_TEST(kmparticle_ptr_null_returns_nonzero)
{
  ck_assert_int_ne(kmparticle(NULL), 0);
}
END_TEST

Suite* mk_particle_suite(void)
{
  Suite* s = suite_create("particle");
  TCase* c = tcase_create("core");

  tcase_add_checked_fixture(c, setup, teardown);
  tcase_add_test(c, mkparticle_works);
  tcase_add_test(c, kmparticle_id_unknown_returns_nonzero);
  tcase_add_test(c, kmparticle_ptr_null_returns_nonzero);
  suite_add_tcase(s, c);

  return s;
}


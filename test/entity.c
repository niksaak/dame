#include "test.h"
#include "../src/entity.h"
#include "../src/module.h"
#include "../src/sys.h"

START_TEST(mkentity_null_returns_bad_entity)
{
  ck_assert_int_eq(mkentity((module_t*)NULL), BAD_ENTITY);
}
END_TEST

START_TEST(mkentity_works)
{
  init_space();
  module_t* m = mkmodule(cpvzero);
  entity_t ent = mkentity(m);

  ck_assert_ptr_ne(m, NULL);
  ck_assert_int_ne(ent, BAD_ENTITY);
  ck_assert_ptr_eq(entity(ent), m);

  kmmodule(m);
  deinit_space();
}
END_TEST

START_TEST(kmentity_bad_entity_returns_nonzero)
{
  ck_assert_int_ne(kmentity(BAD_ENTITY), 0);
}
END_TEST

START_TEST(kmentity_works)
{
  init_space();
  module_t* m = mkmodule(cpvzero);
  entity_t ent = mkentity(m);

  ck_assert_ptr_ne(m, NULL);
  ck_assert_int_ne(ent, BAD_ENTITY);

  ck_assert_int_eq(kmentity(ent), 0);
  ck_assert_ptr_eq(entity(ent), NULL);

  kmmodule(m);
  deinit_space();
}
END_TEST

START_TEST(entity_kind_works)
{
  init_space();
  module_t* m = mkmodule(cpvzero);
  entity_t ent = mkentity(m);

  ck_assert_ptr_ne(m, NULL);
  ck_assert_int_ne(ent, BAD_ENTITY);

  ck_assert_int_eq(entity_kind(ent) == MODULE_ENTITY);

  kmentity(ent);
  deinit_space();
}
END_TEST

START_TEST(entity_kind_bad_entity_returns_bad_entity)
{
  ck_assert_int_eq(entity_kind(BAD_ENTITY), BAD_ENTITY);
}
END_TEST

START_TEST(entity_bad_entity_returs_null)
{
  ck_assert_ptr_eq(entity(BAD_ENTITY), NULL);
}
END_TEST

START_TEST(entity_nonexistant_returns_null)
{
  ck_assert_ptr_eq(entity(413), NULL);
}
END_TEST

START_TEST(sentity_works)
{
  init_space();
  module_t* m = mkmodule(cpvzero);
  entity_t ent = mkentity(m);

  ck_assert_ptr_ne(m, NULL);
  ck_assert_int_ne(ent, BAD_ENTITY);

  ck_assert_ptr_eq(sentity(ent, MODULE_ENTITY), m);
  ck_assert_ptr_eq(sentity(ent, PORT_ENTITY), NULL);

  kmentity(ent);
  deinit_space();
}
END_TEST

Suite* mk_entity_suite(void)
{
  Suite* s = suite_create("entity");
  TCase* c = tcase_create("core");

  tcase_add_test(c, mkentity_null_returns_bad_entity);
  tcase_add_test(c, mkentity_works);
  tcase_add_test(c, kmentity_bad_entity_returns_nonzero);
  tcase_add_test(c, kmentity_works);
  tcase_add_test(c, entity_kind_works);
  tcase_add_test(c, entity_kind_bad_entity_returns_bad_entity);
  tcase_add_test(c, entity_bad_entity_returs_null);
  tcase_add_test(c, entity_nonexistant_returns_null);
  tcase_add_test(c, sentity_works);
  suite_add_tcase(s, c);

  return s;
}


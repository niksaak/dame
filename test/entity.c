#include <check.h>
#include "../src/entity.h"
#include "../src/module.h"

/* entities */

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

START_TEST(kmentity_nil_returns_nonzero)
{
  ck_assert_int_ne(kmentity(NIL_ENTITY), 0);
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

  ck_assert_int_eq(entity_kind(ent), MODULE_ENTITY);

  kmentity(ent);
  deinit_space();
}
END_TEST

START_TEST(entity_kind_bad_entity_returns_bad_entity)
{
  ck_assert_int_eq(entity_kind(BAD_ENTITY), BAD_ENTITY);
}
END_TEST

START_TEST(entity_kind_nil_returns_bad_entity)
{
  ck_assert_int_eq(entity_kind(NIL_ENTITY), BAD_ENTITY);
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

START_TEST(sentity_bad_entity_returns_null)
{
  ck_assert_ptr_eq(sentity(BAD_ENTITY, MODULE_ENTITY), NULL);
}
END_TEST

START_TEST(sentity_nil_returns_null)
{
  ck_assert_ptr_eq(sentity(NIL_ENTITY, MODULE_ENTITY), NULL);
}
END_TEST

/* space */

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

Suite* mk_entity_suite(void)
{
  Suite* s = suite_create("entity");
  TCase* tent = tcase_create("core");
  TCase* tspc = tcase_create("space");

  tcase_add_test(tent, mkentity_null_returns_bad_entity);
  tcase_add_test(tent, mkentity_works);
  tcase_add_test(tent, kmentity_bad_entity_returns_nonzero);
  tcase_add_test(tent, kmentity_nil_returns_nonzero);
  tcase_add_test(tent, kmentity_works);
  tcase_add_test(tent, entity_kind_works);
  tcase_add_test(tent, entity_kind_bad_entity_returns_bad_entity);
  tcase_add_test(tent, entity_kind_nil_returns_bad_entity);
  tcase_add_test(tent, entity_bad_entity_returs_null);
  tcase_add_test(tent, entity_nonexistant_returns_null);
  tcase_add_test(tent, sentity_works);
  tcase_add_test(tent, sentity_bad_entity_returns_null);
  tcase_add_test(tent, sentity_nil_returns_null);

  tcase_add_test(tspc, init_space_returns_current_space);
  tcase_add_test(tspc, remove_body_works);
  tcase_add_test(tspc, remove_body_null_returns_nonzero);

  suite_add_tcase(s, tent);
  suite_add_tcase(s, tspc);

  return s;
}


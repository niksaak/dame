#include "test.h"
#include "../src/entity.h"
#include "../src/module.h"
#include "../src/sys.h"

START_DEFTEST(mkentity_null_returns_bad_entity)
{
  TASSERT(mkentity((module_t*)NULL) == BAD_ENTITY);
}
END_DEFTEST

START_DEFTEST(mkentity_works)
{
  init_space();
  module_t* m = mkmodule(cpvzero);
  entity_t ent = mkentity(m);

  TEASSERT(m != NULL);
  TEASSERT(ent != BAD_ENTITY);
  TEASSERT(entity(ent) == m);

  kmmodule(m);
  deinit_space();
}
END_DEFTEST

START_DEFTEST(kmentity_bad_entity_returns_nonzero)
{
  TASSERT(kmentity(BAD_ENTITY) != 0);
}
END_DEFTEST

START_DEFTEST(kmentity_works)
{
  init_space();
  module_t* m = mkmodule(cpvzero);
  entity_t ent = mkentity(m);

  TEASSERT(m != NULL);
  TEASSERT(ent != BAD_ENTITY);

  TASSERT(kmentity(ent) == 0);
  TASSERT(entity(ent) == NULL);

  kmmodule(m);
  deinit_space();
}
END_DEFTEST

START_DEFTEST(entity_kind_works)
{
  init_space();
  module_t* m = mkmodule(cpvzero);
  entity_t ent = mkentity(m);

  TEASSERT(m != NULL);
  TEASSERT(ent != BAD_ENTITY);

  TASSERT(entity_kind(ent) == MODULE_ENTITY);

  kmentity(ent);
  deinit_space();
}
END_DEFTEST

START_DEFTEST(entity_kind_bad_entity_returns_bad_entity)
{
  TASSERT(entity_kind(BAD_ENTITY) == BAD_ENTITY);
}
END_DEFTEST

START_DEFTEST(entity_bad_entity_returs_null)
{
  TASSERT(entity(BAD_ENTITY) == NULL);
}
END_DEFTEST

START_DEFTEST(entity_nonexistant_return_null)
{
  TASSERT(entity(413) == NULL);
}
END_DEFTEST

START_DEFTEST(sentity_works)
{
  init_space();
  module_t* m = mkmodule(cpvzero);
  entity_t ent = mkentity(m);

  TEASSERT(m != NULL);
  TEASSERT(ent != BAD_ENTITY);

  TASSERT(sentity(ent, MODULE_ENTITY) == m);
  TASSERT(sentity(ent, PORT_ENTITY) == NULL);

  kmentity(ent);
  deinit_space();
}
END_DEFTEST

Tester check_entity(void)
{
  Tester t = {"entity"};

  TEST(mkentity_null_returns_bad_entity, t);
  TEST(mkentity_works, t);
  TEST(kmentity_bad_entity_returns_nonzero, t);
  TEST(kmentity_works, t);
  TEST(entity_kind_works, t);
  TEST(entity_kind_bad_entity_returns_bad_entity, t);
  TEST(entity_bad_entity_returs_null, t);
  TEST(entity_nonexistant_return_null, t);
  TEST(sentity_works, t);

  return t;
}


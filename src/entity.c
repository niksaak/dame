#include "entity.h"

#include <uthash.h>
#include "error.h"

typedef struct Ent {
  entity_t id;
  entity_kind_t kind;
  void* obj;

  UT_hash_handle hh;
} Ent;

static Ent* entv; // entities hash table

/* Helpers */

static void entput(Ent ent)
{
  Ent* e = malloc(sizeof ent); // TODO: check malloc

  if(e == NULL) {
    panic("Bad malloc.");
  }

  *e = ent;
  HASH_ADD_INT(entv, id, e);
}

static Ent* getent(entity_t id)
{
  Ent* e;

  HASH_FIND_INT(entv, &id, e);

  return e;
}

static void entrem(Ent* ent)
{
  HASH_DEL(entv, ent);
  free(ent);
}

static entity_t entgenid(void)
{ // TODO: rename to genid()
  static entity_t id;
  return ++id;
}

/* API */

entity_t mkentity_kind(void* obj, entity_kind_t kind)
{
  if(obj == NULL) {
    return BAD_ENTITY;
  }

  entity_t id = entgenid();
  entput((Ent){ id, kind, obj });
  // TODO: what after I create 4294967294 entities?
  // TODO: consider just checking the id by HASH_FIND()ing it

  return id;
}

int kmentity(entity_t id)
{
  Ent* ent = getent(id);

  if(ent == NULL) {
    error("Entity not found: %i", id);
    return -1;
  }
  entrem(ent);

  return 0;
}

int entity_kind(entity_t id)
{
  Ent* ent = getent(id);

  if(ent == NULL) {
    return -1;
  }

  return ent->kind;
}

void* entity(entity_t id)
{
  if(id == NIL_ENTITY || id == BAD_ENTITY) {
    return NULL;
  }

  Ent* ent = getent(id);

  if(ent == NULL) {
    return NULL;
  }

  return ent->obj;
}

void* sentity(entity_t id, entity_kind_t kind)
{
  if(id == NIL_ENTITY || id == BAD_ENTITY) {
    return NULL;
  }

  Ent* ent = getent(id);

  if(ent == NULL) {
    return NULL;
  }
  if(ent->kind != kind) {
    return NULL;
  }
  return ent->obj;
}

const char* entity_kind_name(entity_kind_t kind)
{
  return NULL; // TODO
}

/* Physics */
// TODO: looks out of place in this header, should consider moving it
//       somewhere else.

static cpSpace* space; // the physics space

cpSpace* init_space(void)
{
  space = cpSpaceNew();
  return space;
}

cpSpace* current_space(void)
{
  if(space == NULL) {
    error("Space is not initialized");
  }
  return space;
}

int deinit_space(void)
{
  cpSpaceFree(space);
  return 0;
}

int remove_body(cpBody* body)
{
  if(body == NULL) {
    error("Bad body");
    return -1; // nyurupo~
  }

  if(space == NULL) {
    error("Space is not initialized");
    return -1;
  }

  cpBodyEachShape_b(body,
      ^(cpShape* s){
        cpSpaceRemoveShape(space, s);
        cpShapeFree(s);
      });
  cpSpaceRemoveBody(space, body);
  cpBodyFree(body);

  return 0;
}


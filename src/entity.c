#include "entity.h"

#include <uthash.h>

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

entity_t entgenid(void)
{
  static entity_t id;
  return id++;
}

/* API */

entity_t mkentity_kind(void* obj, entity_kind_t kind)
{
  if(obj == NULL) {
    return BAD_ENTITY;
  }

  entity_t id = entgenid();
  entput((Ent){ id, kind, obj });
  // TODO: what after I create 4294967296 entities?

  return id;
}

int kmentity(entity_t id)
{
  Ent* ent = getent(id);

  if(ent == NULL) {
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
  Ent* ent = getent(id);

  if(ent == NULL) {
    return NULL;
  }

  return ent->obj;
}

void* sentity(entity_t id, entity_kind_t kind)
{
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


#pragma once

#include <chipmunk/chipmunk.h>

/* ENTITY
 * manage game entities.
 */

typedef int entity_t;
// entity id

typedef enum entity_kind_t {
  MOTHER_ENTITY, // - mothership or just a chunk of joined modules;
                 // entity() must return pointer to module with CORE facility,
                 // if there is any.
  MODULE_ENTITY, // - module, floating in space by itself, all alone.
  PORT_ENTITY // - port, floating in space.
} entity_kind_t;

static const int BAD_ENTITY = -1;
// magic constant for signalling errors
static const int NIL_ENTITY = 0;
// magic constant for absent entities

/* Make Entity */

#define mkentity(obj)                               \
  _Generic((obj),                                   \
      module_t*: mkentity_kind(obj, MODULE_ENTITY), \
      port_t*: mkentity_kind(obj, PORT_ENTITY))
// create entity, deducing its' kind from pointer type

entity_t mkentity_kind(void* obj, entity_kind_t kind);
// create entity

/* Remove Entity */

int kmentity(entity_t id);
// remove entity

/* Get Entity */

int entity_kind(entity_t id);
// get entity kind, or -1 if entity is not found

void* entity(entity_t id);
// get pointer to entity, or NULL if entity is not found

void* sentity(entity_t id, entity_kind_t kind);
// 'safe' entity();
// get pointer to entity if it is of required kind, otherwise get NULL

/* Misc */

const char* entity_kind_name(entity_kind_t kind);
// get name string for kind

/* Physics */

cpSpace* init_space(void);
// initialize space so that you will be able to work with entities and
// related things

cpSpace* current_space(void);
// get current space

int deinit_space(void);
// deinitialize current space

int remove_body(cpBody* body);
// remove body and all its shapes from space and then free them


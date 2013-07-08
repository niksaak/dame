#pragma once

/* MOTHER
 * this header describes data structures nescessary for constructing the
 * GIYGANT MODULAR MOTHERSHIPS and functions for operating on mothership entity
 * as a whole.
 */

#include <chipmunk/chipmunk.h>
#include "vector.h"

struct port_t;
struct module_t;

typedef struct {
} facility_t; // TODO

typedef struct port_kind_t {
  int id; // kind identifier
  const char* name; // kind namestring
  int (*mk)(struct port_t* port); // port initializer
  int (*km)(struct port_t* port); // port deinitializer
  int (*draw)(struct port_t* port); // draw port
} port_kind_t;

typedef struct port_t {
  const port_kind_t* spec;
  struct module_t* module; // module which this port is attached to
  void* data; // port internal data

  cpBody* body;
} port_t;

typedef struct module_t {
  facility_t fac;
  port_t* ports[4]; // module ports, from eastern one counterclockwise
                    // (port[0] is at 0°, port[3] is at 270°)
  cpBody* body;
} module_t;


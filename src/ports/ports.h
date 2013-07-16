#pragma once

#include "../mother.h"

typedef enum port_id_t {
  NIL_PORT_ID = 0,
  DOCKING_PORT_ID,
  RCS_PORT_ID,
  THRUSTER_PORT_ID,

  PORT_ID_MAX
} port_id_t;

typedef const port_kind_t* const PORT_KIND_DECL;


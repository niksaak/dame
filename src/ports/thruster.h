#pragma once

#include "ports_util.h"

PORT_KIND_DECL THRUSTER_PORT_KIND;

double thruster_getpower(port_t* port);
  // get thruster power;
  // returns negative value on error

int thruster_setpower(port_t* port, double power);
  // set thruster power;
  // returns nonzero on error


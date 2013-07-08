#pragma once

#include "../mother.h"

double thruster_getpower(port_t* port);
  // get thruster power;
  // returns negative value on error

int thruster_setpower(port_t* port, double power);
  // set thruster power;
  // returns nonzero on error


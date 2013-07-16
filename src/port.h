#pragma once

#include "mother.h"
#include "ports/rcs.h"
#include "ports/thruster.h"

port_t* mkport(const port_kind_t* kind, cpVect pos);

int kmport(port_t* port);


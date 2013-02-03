#pragma once

#include "entity.h"

extern Entity* emit_particle(cpSpace* space, cpBody* body,
    cpVect offset, cpVect impulse);

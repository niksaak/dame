#pragma once

/* MODULE
 * this header provides functions for creating, destroying and doing things
 * with mothership modules.
 */

#include "mother.h"

module_t* mkmodule(cpVect pos);
    // create module at `pos`

int kmmodule(module_t* module);
    // kill the module

int draw_module(const module_t* module);
    // draw the module

int module_mkport(module_t* module, int place, int kind);
    // make port of `kind` and attach it to `module` at `place`

int module_kmport(module_t* module, int place);
    // kill port attached to `module` at `place`

int punch_module(module_t* module, cpVect direction);


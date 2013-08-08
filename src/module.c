#include "module.h"

#include <stdlib.h>
#include "sys.h"
#include "util.h"
#include "draw.h"
#include "port.h"

static const cpVect shapev[] = {
  { -1, 1 },
  { 1, 1 },
  { 1, -1 },
  { -1, -1 }
};
static const size_t shapec = ARRLEN(shapev, cpVect);
static const cpFloat mass = 2;


static cpFloat moi(void)
{
  static cpFloat i = 0;
  if(i == 0) {
    i = cpMomentForPoly(mass, shapec, shapev, cpvzero);
  }
  return i;
}

module_t* mkmodule(cpVect pos)
{
  module_t* m = malloc(sizeof *m);
  if(m == NULL) {
    return NULL; // malloc
  }

  cpSpace* space = current_space();
  if(space == NULL) {
    return NULL; // space
  }

  cpBody* body = cpBodyNew(mass, moi());
  cpShape* shape = cpPolyShapeNew(body, shapec, shapev, cpvzero);
  int id = genid();

  *m = (module_t){
    .id = id,
    .fac = {0},
    .ports = {0},
    .body = body
  };

  cpBodySetUserData(body, m);
  cpShapeSetUserData(shape, m);
  cpShapeSetGroup(shape, id);

  cpSpaceAddBody(space, body);
  cpSpaceAddShape(space, shape);

  return m;
}

int kmmodule(module_t* module)
{
  if(module == NULL) {
    return -1;
  }
  if(module->body != NULL) {
    cpBodyEachShape_b(module->body, ^(cpShape* shape){ cpShapeFree(shape); } );
    cpBodyFree(module->body);
  }
  free(module);
  return 0;
}

int draw_module(const module_t* module)
{
  if(module == NULL) {
    return -1; // nutupo~
  }

  int ret = 0;

  cpVect pos = cpBodyGetPos(module->body);
  glPushMatrix();
  glLoadIdentity(); // TODO: moving camera
  glTranslated(pos.x, pos.y, 0);
  ret |= draw_polygon((Vec*)shapev, shapec);
  for(port_t* const * p = module->ports; p < (module->ports + 4); p++) {
    if(*p != NULL) {
      draw_port(*p);
    }
  }
  glPopMatrix();
  return ret;
}

static int rotate_port(port_t* p, module_t* m, int place)
{
  cpVect ppos = cpBodyWorld2Local(m->body, cpBodyGetPos(p->body));

  switch(place) {
    case 0:
      break;
    case 1:
      cpBodySetAngle(p->body, QUADCIRCLE);
      ppos = cpvperp(ppos);
      break;
    case 2:
      cpBodySetAngle(p->body, SEMICIRCLE);
      ppos = cpvneg(ppos);
      break;
    case 3:
      cpBodySetAngle(p->body, -QUADCIRCLE);
      ppos = cpvrperp(ppos);
      break;
    default: return -1; // bad place
  }

  cpBodySetPos(p->body, cpBodyLocal2World(m->body, ppos));

  return 0;
}

int module_mkport(module_t* module, int place, const port_kind_t* kind)
{ // TODO
  port_t* p = mkport(kind, cpvadd(cpBodyGetPos(module->body), (cpVect){1,0}));

  if(rotate_port(p, module, place)) {
    return -1; // rotation unsuccessful
  }
  module->ports[place] = p;

  return 0;
}

int module_kmport(module_t* module, int place)
{
  port_t* p = module->ports[place];
  if(p == NULL) {
    return -1; // TODO: warn here
  }

  module->ports[place] = NULL;
  kmport(p);

  return 0;
}


#include "module.h"

#include <stdlib.h>
#include "sys.h"
#include "util.h"
#include "draw.h"

static const cpVect shapev[] = {
  { -1, 1 },
  { 1, 1 },
  { 1, -1 },
  { -1, -1 }
};
static const size_t shapec = ARRLEN(shapev, cpVect);

static const cpFloat mass = 20;

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

  *m = (module_t){
    // .fac = {0}, // TODO
    .ports = {0},
    .body = body
  };

  cpBodySetUserData(body, m);
  cpShapeSetUserData(shape, m);
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
  int ret;

  Vec pos = cpv2vec(cpBodyGetPos(module->body));
  glPushMatrix();
  glTranslated(pos.x, pos.y, 0);
  ret = draw_polygon((Vec*)shapev, shapec);
  glPopMatrix();
  return ret;
  // TODO: draw module ports, if any, too
}

int module_mkport(module_t* module, int place, int kind)
{
  return -1; // TODO
}

int module_kmport(module_t* module, int place)
{
  return -1; // TODO
}


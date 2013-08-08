#include "thruster.h"

#include <chipmunk/chipmunk.h>
#include "../sys.h"
#include "../util.h"
#include "../draw.h"

static cpVect shapev[] = {
  { 0, 0.5 },
  { 0.25, 1 },
  { 0.5, 1 },
  { 0.5, -1 },
  { 0.25, -1 },
  { 0, -0.5 }
};
static const size_t shapec = ARRLEN(shapev, cpVect);
static const cpFloat mass = 0.3;


static cpFloat moi(void)
{
  static cpFloat i = 0;
  if(i == 0) {
    i = cpMomentForPoly(mass, shapec, shapev, cpvzero);
  }
  return i;
}

int mk(port_t* port)
{
  cpSpace* space = current_space();
  cpBody* body = cpBodyNew(mass, moi());
  cpShape* shape = cpPolyShapeNew(body, shapec, shapev, cpvzero);
  double* thrust = calloc(1, sizeof *thrust);

  if(space == NULL) {
    return -1;
  }
  if(body == NULL) {
    return -1;
  }
  if(shape == NULL) {
    return -1;
  }
  if(thrust == NULL) {
    return -1;
  }

  *port = (port_t) {
    .kind = THRUSTER_PORT_KIND,
    .module = NULL,
    .data = thrust,
    .body = body
  };

  cpBodySetUserData(body, port);
  cpShapeSetUserData(shape, port);
  cpSpaceAddBody(space, body);
  cpSpaceAddShape(space, shape);

  return 0;

}

int km(port_t* port)
{
  if(port->kind != THRUSTER_PORT_KIND) {
    return -1;
  }

  free(port->data);
  remove_body(port->body);
  /*
  cpBodyEachShape_b(port->body,
                    ^(cpShape* shape) {
        cpSpaceRemoveShape(space, shape);
        cpShapeFree(shape);
      }
  );
  cpSpaceRemoveBody(space, port->body);
  cpBodyFree(port->body);
  */

  return 0;
}

double thruster_getpower(port_t* port)
{
  if(port == NULL) {
    return -1; // nyurupo~
  }
  if(port->kind == NULL) {
    return -1; // nyurupo
  }
  if(port->data == NULL) {
    return -1; // nyurupo~
  }

  return *(double*)port->data;
};

int thruster_setpower(port_t* port, double power)
{
  if(port == NULL) {
    return -1; // nyurupo~
  }
  if(port->kind == NULL) {
    return -1; // nyurupo~
  }
  if(port->data == NULL) {
    return -1; // nyurupo~
  }

  double* pow = port->data;
  *pow = power;

  return 0;
}

static int draw(port_t* port)
{
  cpVect pos = cpBodyGetPos(port->body);
  int ret;

  glPushMatrix();
  {
    glLoadIdentity();
    glTranslated(pos.x, pos.y, 0);
    ret = draw_polygon((Vec*)shapev, shapec);
  }
  glPopMatrix();

  return ret;
}

static const port_kind_t kind = {
  .name = "thruster",
  .mk = mk,
  .km = km,
  .draw = draw
};

const port_kind_t* const THRUSTER_PORT_KIND;


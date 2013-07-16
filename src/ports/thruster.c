#include "thruster.h"

#include <chipmunk/chipmunk.h>
#include "../sys.h"
#include "../util.h"

cpVect shapev[] = {
  { 0, 0.5 },
  { 0.25, 1 },
  { 0.5, 1 },
  { 0.5, -1 },
  { 0.25, -1 },
  { 0, -0.5 }
};

size_t shapec = ARRLEN(shapev, cpVect);

cpFloat mass = 0.3;


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

  cpSpace* space = current_space();

  free(port->data);
  cpBodyEachShape_b(port->body,
                    ^(cpShape* shape) {
        cpSpaceRemoveShape(space, shape);
        cpShapeFree(shape);
      }
  );
  cpSpaceRemoveBody(space, port->body);
  cpBodyFree(port->body);

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
  if(port->kind->id != THRUSTER_PORT_ID) {
    return -1; // bad enum
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
  if(port->kind->id != THRUSTER_PORT_ID) {
    return -1; // bad enum
  }
  if(port->data == NULL) {
    return -1; // nyurupo~
  }

  double* pow = port->data;
  *pow = power;

  return 0;
}


static const port_kind_t kind = {
  .id = THRUSTER_PORT_ID,
  .name = "thruster",
  .mk = mk,
  .km = km,
  .draw = NULL
};

const port_kind_t* const THRUSTER_PORT_KIND;

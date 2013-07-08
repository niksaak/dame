#include "rcs.h"

#include <chipmunk/chipmunk.h>
#include "../sys.h"
#include "../util.h"
#include "../draw.h"
#include "ports.h"

static const cpVect shapev[] = {
  { 0    ,  0.5  },
  { 0.25 ,  1    },
  { 0.75 ,  1    },
  { 0    ,  0.25 },
  { 0    , -0.25 },
  { 0.75 , -1    },
  { 0.25 , -1    },
  { 1    , -0.5  }
};
static const size_t shapec = ARRLEN(shapev, cpVect);

static const cpFloat mass = 0.5;


static cpFloat moi(void)
{ // moment of inertia
  static cpFloat m = 0;
  if(m == 0) {
    m = cpMomentForPoly(mass, shapec, shapev, cpvzero);
  }
  return m;
}

static int mk(port_t* port)
{
  if(port == NULL) {
    return -1; // nurupo~
  }

  cpSpace* space = current_space();
  cpBody* body = cpBodyNew(mass, moi());
  cpShape* shape = cpPolyShapeNew(body, shapec, shapev, cpvzero);

  *port = (port_t){
    .spec = &RCS_PORT_SPEC,
    .module = NULL,
    .data = NULL,
    .body = body
  };

  cpBodySetUserData(body, port);
  cpShapeSetUserData(shape, port);
  cpSpaceAddBody(space, body);
  cpSpaceAddShape(space, shape);

  return 0;
}

static int km(port_t* port)
{
  if(port->body == NULL) {
    return -1; // nurupo~
  }

  cpSpace* space = current_space();
  if(space == NULL) {
    return -1; // space
  }

  if(port->body) {
    cpBodyEachShape_b(port->body, ^(cpShape* shape) {
          cpSpaceRemoveShape(space, shape);
          cpShapeFree(shape);
        }
    );
    cpSpaceRemoveBody(space, port->body);
    cpBodyFree(port->body);
  }
  *port = (port_t){0};

  return 0;
}

static int draw(port_t* port)
{
  return draw_polygon((Vec*)shapev, shapec);
}


const port_kind_t RCS_PORT_KIND = {
  .id = RCS_PORT_ID,
  .name = "rcs",
  .mk = mk,
  .km = km,
  .draw = draw
};

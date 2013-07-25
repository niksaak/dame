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
  cpSpace* space = current_space();
  cpBody* body = cpBodyNew(mass, moi());
  cpShape* shape = cpPolyShapeNew(body, shapec, shapev, cpvzero);

  *port = (port_t){
    .kind = RCS_PORT_KIND,
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
  if(port->kind != RCS_PORT_KIND) {
    return -1;
  }

  cpSpace* space = current_space();
  if(space == NULL) {
    return -1; // space
  }

  remove_body(port->body, space);
  /*
  cpBodyEachShape_b(port->body, ^(cpShape* shape) {
        cpSpaceRemoveShape(space, shape);
        cpShapeFree(shape);
      }
  );
  cpSpaceRemoveBody(space, port->body);
  cpBodyFree(port->body);
  */

  *port = (port_t){0};

  return 0;
}

static int draw(port_t* port)
{
  return draw_polygon((Vec*)shapev, shapec);
}


static const port_kind_t kind = {
  .id = RCS_PORT_ID,
  .name = "rcs",
  .mk = mk,
  .km = km,
  .draw = draw
};

const port_kind_t* const RCS_PORT_KIND = &kind;


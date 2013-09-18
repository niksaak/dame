#include "port.h"

#include <GLFW/glfw3.h>
#include "error.h"
#include "entity.h"
#include "util.h"
#include "ports/rcs.h"
#include "ports/thruster.h"

port_t* mkport(const port_kind_t* kind, cpVect pos)
{
  if(kind == NULL) {
    error("Kind is NULL");
    return NULL; // nyurupo~
  }
  if(kind->mk == NULL) {
    error("Kinds' mk() is not implemented");
    return NULL; // not implemented
  }

  port_t* p = malloc(sizeof *p);
  p->id = -1; // TODO
  if(kind->mk(p)) {
    error("Making port unsuccessful");
    return NULL;
  }

  cpBodySetPos(p->body, pos);

  return p;
}

int kmport(port_t* port)
{
  if(port == NULL) {
    error("Port is already NULL");
    return -1; // nyurupo~
  }
  if(port->kind == NULL) {
    error("Ports' kind is NULL");
    return -1; // bad port
  }
  if(port->kind->km == NULL) {
    error("Ports' km() is not implemented");
    return -1; // not implemented
  }

  cpSpace* space = current_space();

  cpBodyEachConstraint_b(port->body,
      ^(cpConstraint* c) { cpSpaceRemoveConstraint(space, c); });
  int ret = port->kind->km(port);
  free(port);

  return ret;
}

int draw_port(port_t* port)
{
  if(port == NULL) {
    error("Port is NULL.");
    return -1; // nyurupo~
  }
  if(port->body == NULL) {
    error("Body is NULL.");
    return -1; // no body
  }
  if(port->kind->draw == NULL) {
    error("draw() is not implemented for this kind");
    return -1; // not implemented
  }

  cpVect pos = cpBodyGetPos(port->body);
  cpFloat ang = cpBodyGetAngle(port->body);
  int ret = 0;

  glPushMatrix();
  {
    glLoadIdentity();
    glTranslated(pos.x, pos.y, 0);
    glRotated(ang, 0, 0, 0);
    ret = port->kind->draw(port);
  }
  glPopMatrix();

  return ret;
}


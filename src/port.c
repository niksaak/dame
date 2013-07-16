#include "port.h"

#include "ports/rcs.h"
#include "ports/thruster.h"

port_t* mkport(const port_kind_t* kind, cpVect pos)
{
  if(kind == NULL) {
    return NULL; // nyurupo~
  }
  if(kind->id >= PORT_ID_MAX || kind->id < 0) {
    return NULL; // bad kind
  }
  if(kind->mk == NULL) {
    return NULL; // not implemented
  }

  port_t* p = malloc(sizeof *p);

  if(kind->mk(p)) {
    return NULL; // TODO error handling
  }
  cpBodySetPos(p->body, pos);

  return p;
}

int kmport(port_t* port)
{
  if(port == NULL) {
    return -1; // nyurupo~
  }
  if(port->kind == NULL) {
    return -1; // bad port
  }
  if(port->kind->km == NULL) {
    return -1; // not implemented
  }

  int ret = port->kind->km(port);
  free(port);

  return ret;
}


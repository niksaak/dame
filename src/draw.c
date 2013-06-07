#include "draw.h"

#include <math.h>

#include "main.h"

/* Drawing primitives */

int draw_points(const cpVect coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_POINTS, 0, count);
  glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

int draw_polyline(const cpVect coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_LINE_STRIP, 0, count);
  glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

int draw_polygon(const cpVect coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_LINE_LOOP, 0, count);
  glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

static cpVect decasteljau(const cpVect vects[], size_t count, double t)
{
  cpVect v[count];

  for(int i = 0; i < count; i++) {
    v[i] = vects[i];
  }
  for(int k = 1; k < count; k++) {
    for(int i = 0; i < (count - k); i++) {
      v[i] = cpvlerp(v[i], v[i + 1], t);
    }
  }

  return v[0];
}

int draw_curve(const cpVect coords[], size_t count)
{
  int segc = 0;
  int ret;
  cpVect* curve;

  if(coords == NULL) {
    return -1; // nurupo~
  }
  for(int i = 0, j = 1; j < count; i++, j++) {
    segc += ceil(cpvdist(coords[i], coords[j]) * 16);
  }
  curve = malloc(sizeof (cpVect) * segc);
  if(curve == NULL) {
    return -1; // malloc error
  }
  for(int i = 0; i < segc; i++) {
    curve[i] = decasteljau(coords, count, (double)i / segc);
  }
  ret = draw_polyline(curve, segc);
  free(curve);
  return ret;
}

int draw_vects(DrawingMode mode, const cpVect vects[], size_t count)
{
  if(vects == NULL) {
    return -1; // nurupo~
  }
  switch(mode) {
    case DRAW_POINTS:
      return draw_points(vects, count);
    case DRAW_POLYLINE:
      return draw_polyline(vects, count);
    case DRAW_CURVE:
      return draw_curve(vects, count);
    case DRAW_POLYGON:
      return draw_polygon(vects, count);
    default:
      return -1; // bad enum
  }

  return -1;
}

int draw_circle(cpVect pos, double radius)
{ // algorithm from here: http://slabode.exofire.net/circle_draw.shtml
  static cpVect verts[360];
  static const size_t vertc = sizeof verts / sizeof (cpVect);
  double theta = 2 * M_PI / vertc;
  double costh = cos(theta);
  double sinth = sin(theta);
  double t;
  double x = radius;
  double y = 0;

  for(int i = 0; i < vertc; i++) {
    verts[i].x = x + pos.x;
    verts[i].y = y + pos.y;

    t = x;
    x = costh * x - sinth * y;
    y = sinth * t + costh * y;
  }

  return draw_polygon(verts, vertc);
}

int draw_square(cpVect pos, double side)
{
  GLdouble r = side / 2.0;
  GLdouble x = pos.x;
  GLdouble y = pos.y;
  cpVect square[4] = {
    { x + r, y + r },
    { x + r, y - r },
    { x - r, y - r },
    { x - r, y + r }
  };

  return draw_polygon(square, 4);
}

int draw_rectangle(cpVect pos, double width, double height)
{
  GLdouble cw = width / 2.0;
  GLdouble ch = height / 2.0;
  cpVect square[4] = {
    { pos.x + cw, pos.y + ch },
    { pos.x + cw, pos.y - ch },
    { pos.x - cw, pos.y - ch },
    { pos.x - cw, pos.y + ch }
  };

  return draw_polygon(square, 4);
}

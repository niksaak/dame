#include "draw.h"

#include <math.h>

/* Drawing primitives */

int draw_points(const Vec coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  //glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_POINTS, 0, count);
  //glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

int draw_polyline(const Vec coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  //glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_LINE_STRIP, 0, count);
  //glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

int draw_polygon(const Vec coords[], size_t count)
{
  if(coords == NULL) {
    return -1; // nurupo~
  }
  //glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_DOUBLE, 0, coords);
  glDrawArrays(GL_LINE_LOOP, 0, count);
  //glDisableClientState(GL_VERTEX_ARRAY);
  return 0;
}

static Vec decasteljau(const Vec vects[], size_t count, double t)
{
  Vec v[count];

  for(int i = 0; i < count; i++) {
    v[i] = vects[i];
  }
  for(int k = 1; k < count; k++) {
    for(int i = 0; i < (count - k); i++) {
      v[i] = veclerp(v[i], v[i + 1], t);
    }
  }

  return v[0];
}

int draw_curve(const Vec coords[], size_t count)
{
  int segc = 0;
  int ret;
  Vec* curve;

  if(coords == NULL) {
    return -1; // nurupo~
  }
  for(int i = 0, j = 1; j < count; i++, j++) {
    segc += ceil(vecdist(coords[i], coords[j]) * 16);
  }
  curve = malloc(sizeof (Vec) * segc);
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

int draw_circle(Vec pos, double radius)
{ // drawing algorithm from here: http://slabode.exofire.net/circle_draw.shtml
  static Vec verts[360];
  static const size_t vertc = sizeof verts / sizeof (Vec);
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

int draw_square(Vec pos, double side)
{
  GLdouble r = side / 2.0;
  GLdouble x = pos.x;
  GLdouble y = pos.y;
  Vec square[4] = {
    { x + r, y + r },
    { x + r, y - r },
    { x - r, y - r },
    { x - r, y + r }
  };

  return draw_polygon(square, 4);
}

int draw_rectangle(Vec pos, double width, double height)
{
  GLdouble cw = width / 2.0;
  GLdouble ch = height / 2.0;
  Vec square[4] = {
    { pos.x + cw, pos.y + ch },
    { pos.x + cw, pos.y - ch },
    { pos.x - cw, pos.y - ch },
    { pos.x - cw, pos.y + ch }
  };

  return draw_polygon(square, 4);
}


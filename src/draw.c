#include "draw.h"

#include <math.h>

/* Drawing primitives */

int draw_points(const Vec coords[], size_t count)
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

int draw_polyline(const Vec coords[], size_t count)
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

int draw_polygon(const Vec coords[], size_t count)
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

int draw_vects(DrawingMode mode, const Vec vects[], size_t count)
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

int draw(const Drawing* drawing)
{
  if(drawing == NULL) {
    return -1; // nurupo~
  }
  switch(drawing->mode) {
    case DRAW_POINTS:
      draw_points(drawing->ver.vecs, drawing->ver.count);
      break;
    case DRAW_POLYLINE:
      draw_polyline(drawing->ver.vecs, drawing->ver.count);
      break;
    case DRAW_POLYGON:
      draw_polygon(drawing->ver.vecs, drawing->ver.count);
      break;
    case DRAW_CURVE:
      draw_curve(drawing->ver.vecs, drawing->ver.count);
      break;
    case DRAW_CIRCLE:
      draw_circle(drawing->par.pos, drawing->par.params[0]);
      break;
    case DRAW_SQUARE:
      draw_square(drawing->par.pos, drawing->par.params[0]);
      break;
    case DRAW_RECTANGLE:
      draw_rectangle(drawing->par.pos,
                     drawing->par.params[0], drawing->par.params[1]);
      break;
    default:
      return -1; // bad enum
  }

  if(drawing->on_draw != NULL) {
    if(drawing->on_draw(drawing)) {
      return -1; // error in callback
    }
  }

  return 0;
}

int drawarr(const Drawing* array)
{
  int ret = 0;

  do {
    ret |= draw(array);
    array += sizeof (Drawing);
  } while((array->mode != DRAW_END) & !ret);

  return ret;
}


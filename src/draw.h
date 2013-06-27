#pragma once

#include <GLFW/glfw3.h>
#include <chipmunk/chipmunk.h>

#include "vector.h"

typedef enum DrawingMode {
  DRAW_END = 0, // null-terminator for drawing arrays
  // Arrays
  DRAW_POINTS,
  DRAW_POLYLINE,
  DRAW_POLYGON,
  DRAW_CURVE,

  // Regular shapes
  DRAW_CIRCLE,
  DRAW_SQUARE,
  DRAW_RECTANGLE
} DrawingMode;

typedef struct VDrawing { // Vertices drawing
  DrawingMode mode;
  size_t count; // vertices count
  Vec* vecs; // vertises array
} ADrawing;

typedef struct PDrawing { // Parameterized drawing
  DrawingMode mode;
  Vec pos; // position for the center of drawing
  double params[2]; // params for drawing
} RDrawing;

typedef union Drawing {
  DrawingMode mode;
  ADrawing ver;
  RDrawing par;
} Drawing;

/* Drawing primitives */
// Return nonzero on error.

int draw_points(const Vec coords[], size_t count);
int draw_polyline(const Vec coords[], size_t count);
int draw_polygon(const Vec coords[], size_t count);
int draw_curve(const Vec coords[], size_t count);
int draw_vects(DrawingMode mode, const Vec vects[], size_t count);

int draw_circle(Vec pos, double radius);
int draw_square(Vec pos, double side);
int draw_rectangle(Vec pos, double width, double height);

inline int draw(const Drawing* drawing)
{
  if(drawing == NULL) {
    return -1; // nurupo~
  }
  switch(drawing->mode) {
    case DRAW_POINTS:
      return draw_points(drawing->ver.vecs, drawing->ver.count);
    case DRAW_POLYLINE:
      return draw_polyline(drawing->ver.vecs, drawing->ver.count);
    case DRAW_POLYGON:
      return draw_polygon(drawing->ver.vecs, drawing->ver.count);
    case DRAW_CURVE:
      return draw_curve(drawing->ver.vecs, drawing->ver.count);
    case DRAW_CIRCLE:
      return draw_circle(drawing->par.pos, drawing->par.params[0]);
    case DRAW_SQUARE:
      return draw_square(drawing->par.pos, drawing->par.params[0]);
    case DRAW_RECTANGLE:
      return draw_rectangle(drawing->par.pos,
                            drawing->par.params[0], drawing->par.params[1]);
    default:
      return -1; // bad enum
  }
  return -1;
}

inline int drawarr(const Drawing* array)
{ // draw array of drawings
  int ret = 0;

  do {
    ret |= draw(array);
    array += sizeof (Drawing);
  } while((array->mode != DRAW_END) & !ret);

  return ret;
}


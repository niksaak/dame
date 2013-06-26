#pragma once

#include <GL/glfw.h>
#include <chipmunk/chipmunk.h>

#include "vector.h"

typedef enum DrawingMode {
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

typedef struct ADrawing {
  enum DrawingMode mode;
  size_t count;
  Vec vecs[];
} ADrawing;

typedef struct RDrawing {
  enum DrawingMode mode;
  Vec pos;
  double params[2];
} RDrawing;

typedef union Drawing {
  enum DrawingMode mode;
  ADrawing ard;
  RDrawing red;
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

inline int draw(Drawing* drawing)
{
  if(drawing == NULL) {
    return -1; // nurupo~
  }
  switch(drawing->mode) {
    case DRAW_POINTS:
      return draw_points(drawing->ard.vecs, drawing->ard.count);
    case DRAW_POLYLINE:
      return draw_polyline(drawing->ard.vecs, drawing->ard.count);
    case DRAW_POLYGON:
      return draw_polygon(drawing->ard.vecs, drawing->ard.count);
    case DRAW_CURVE:
      return draw_curve(drawing->ard.vecs, drawing->ard.count);
    case DRAW_CIRCLE:
      return draw_circle(drawing->red.pos, drawing->red.params[0]);
    case DRAW_SQUARE:
      return draw_square(drawing->red.pos, drawing->red.params[0]);
    case DRAW_RECTANGLE:
      return draw_rectangle(drawing->red.pos,
                            drawing->red.params[0], drawing->red.params[1]);
    default:
      return -1; // bad enum
  }
  return -1;
}


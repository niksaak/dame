#pragma once

#include <GLFW/glfw3.h>
#include <chipmunk/chipmunk.h>

#include "vector.h"

struct Drawing;

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
} VDrawing;

typedef struct PDrawing { // Parameterized drawing
  DrawingMode mode;
  Vec pos; // position for the center of drawing
  double params[2]; // params for drawing
} PDrawing;

typedef struct Drawing {
  union {
  DrawingMode mode;
  VDrawing ver;
  PDrawing par;
  }
  int (*on_draw)(struct Drawing* drawing); // drawing callback
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

int draw(const Drawing* drawing);
int drawarr(const Drawing* array)

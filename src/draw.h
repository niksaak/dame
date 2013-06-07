#pragma once

#include <GL/glfw.h>
#include <chipmunk/chipmunk.h>

typedef enum DrawingMode {
  DRAW_POINTS,
  DRAW_POLYLINE,
  DRAW_POLYGON,
  DRAW_CURVE
} DrawingMode;

/* Drawing primitives */
// Return nonzero on error.

int draw_points(const cpVect coords[], size_t count);
int draw_polyline(const cpVect coords[], size_t count);
int draw_polygon(const cpVect coords[], size_t count);
int draw_curve(const cpVect coords[], size_t count);
int draw_vects(DrawingMode mode, const cpVect vects[], size_t count);

int draw_circle(cpVect pos, double radius);
int draw_square(cpVect pos, double side);
int draw_rectangle(cpVect pos, double width, double height);


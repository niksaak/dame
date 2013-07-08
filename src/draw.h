#pragma once

/* DRAW
 *
 * this header provides functions for drawing thingies.
 * to use them, you need first initialize graphics with start_gfx() function
 * from sys.h header
 */

#include <GLFW/glfw3.h>
#include <chipmunk/chipmunk.h>

#include "vector.h"

/* Drawing primitives */
// Return nonzero on error.

int draw_points(const Vec coords[], size_t count);
int draw_polyline(const Vec coords[], size_t count);
int draw_polygon(const Vec coords[], size_t count);
int draw_curve(const Vec coords[], size_t count);

int draw_circle(Vec pos, double radius);
int draw_square(Vec pos, double side);
int draw_rectangle(Vec pos, double width, double height);


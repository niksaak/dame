#pragma once

/* DRAW
 * this header provides functions for drawing thingies.
 * to use them, you need first to initialize graphics with start_gfx()
 */

#include <GLFW/glfw3.h>
#include <chipmunk/chipmunk.h>

#include "vector.h"

/* GL */

// Sys:

int start_gfx(const char* title, int width, int height);
// do necessary preparations and initializations

int stop_gfx(void);
// deinitialize graphics

const char* gl_strerror(GLenum error);
// get string representation of GL error

GLFWwindow* current_window(void);
// get current window

// Rendering:

int render(void);
// render and swap buffers

double zoom(void);
// get zoom factor

double setzoom(double f);
// get zoom factor then set it to f

/* Drawing primitives */
// Return nonzero on error.

int draw_points(const Vec coords[], size_t count);
int draw_polyline(const Vec coords[], size_t count);
int draw_polygon(const Vec coords[], size_t count);
int draw_curve(const Vec coords[], size_t count);

int draw_circle(Vec pos, double radius);
int draw_square(Vec pos, double side);
int draw_rectangle(Vec pos, double width, double height);


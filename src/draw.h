#pragma once

#include <GL/glfw.h>
#include <chipmunk/chipmunk.h>

typedef double vec2_t[2];
typedef double vec3_t[3];
typedef double vec4_t[4];

/* Tools */
int setup_gfx(int width, int height);
    // do necessary preparations and initializations

int render(void);
    // render and swap buffers

/* Drawing primitives */
// Return nonzero on error.

int draw_points(vec2_t* coords, size_t count);
int draw_polyline(vec2_t* coords, size_t count);
int draw_polygon(vec2_t* coords, size_t count);
int draw_circle(vec2_t pos, GLdouble radius);
int draw_square(vec2_t pos, GLdouble side);


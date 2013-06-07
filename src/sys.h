#pragma once

int setup_gfx(int width, int height);
    // do necessary preparations and initializations

int render(void);
    // render and swap buffers

double zoom(double factor);
    // set zoom factor and return it, or just return it if 'factor' is zero


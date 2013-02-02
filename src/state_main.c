#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "engine/system.h"
#include "states.h"

typedef struct SDL_Point {
  int x;
  int y;
} SDL_Point;

struct {
  cpShape* shape;
} ground;

struct {
  cpBody* body;
  cpShape* shape;
} ball;

cpVect gravity;
cpSpace* space = NULL;

SDL_Point cpv_to_SDL(cpVect vector, SDL_Surface* screen, cpVect offset)
{
  int w = screen->w;
  int h = screen->h;
  int x = vector.x;
  int y = vector.y;
  SDL_Point xy;

  xy.x = (w / 2) + x;
  xy.y = (h / 2) - y;

  return xy;
}

void init()
{
  space = cpSpaceNew();
  cpSpaceSetGravity(space, cpv(0, -100));
  
  ground.shape = cpSegmentShapeNew(space->staticBody,
                     cpv(-20,5), cpv(20, -5), 0);
  cpShapeSetFriction(ground.shape, 1);
  cpSpaceAddShape(space, ground.shape);

  ball.body = cpSpaceAddBody(
                  space,
                  cpBodyNew(1, cpMomentForCircle(1, 0, 5, cpvzero)));
  cpBodySetPos(ball.body, cpv(0, 15));

  ball.shape = cpSpaceAddShape(
                   space,
                   cpCircleShapeNew(ball.body, 5, cpvzero));
  cpShapeSetFriction(ball.shape, 0.7);
}

void wake()
{ }

void do_world(cpFloat step)
{
  cpSpaceStep(space, step);
}

void do_render()
{
  SDL_Surface* screen = get_screen();

  void draw_ground()
  {
    SDL_Point pta = cpv_to_SDL(
                        cpSegmentShapeGetA(ground.shape), screen, cpvzero);
    SDL_Point ptb = cpv_to_SDL(
                        cpSegmentShapeGetB(ground.shape), screen, cpvzero);

    aalineColor(screen, pta.x, pta.y, ptb.x, ptb.y, 0xffffffff);
  }

  void draw_ball()
  {
    Sint16 radius = cpCircleShapeGetRadius(ball.shape);
    SDL_Point pos = cpv_to_SDL(
                        cpBodyGetPos(ball.body), screen, cpvzero);
    aacircleColor(screen, pos.x, pos.y, radius, 0xffffffff);
  }

  draw_ground();
  draw_ball();
}

void sleep()
{ }

void deinit()
{
  cpShapeFree(ball.shape);
  cpBodyFree(ball.body);
  cpShapeFree(ground.shape);
  cpSpaceFree(space);
}

state_t state_main()
{
  state_t s;

  s.init = &init;
  s.wake = &wake;
  s.do_world = &do_world;
  s.do_render = &do_render;
  s.sleep = &sleep;
  s.deinit = &deinit;

  return s;
}


#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "engine/engine.h"
#include "states.h"

struct {
  cpShape* shape;
} ground;

struct {
  cpBody* body;
  cpShape* shape;
} ball;

cpVect gravity;
cpSpace* space = NULL;

static void init()
{
  space = cpSpaceNew();
  cpSpaceSetGravity(space, cpv(0, -100));
  
  ground.shape = cpSegmentShapeNew(space->staticBody,
                     cpv(-20,5), cpv(20, -5), 0);
  cpSpaceAddShape(space, ground.shape);
  cpShapeSetFriction(ground.shape, 1);
  cpShapeSetElasticity(ground.shape, 0.3);

  ball.body = cpSpaceAddBody(
                  space,
                  cpBodyNew(1, cpMomentForCircle(1, 0, 5, cpvzero)));
  cpBodySetPos(ball.body, cpv(0, 150));

  ball.shape = cpSpaceAddShape(
                   space,
                   cpCircleShapeNew(ball.body, 5, cpvzero));
  cpShapeSetFriction(ball.shape, 0.7);
  cpShapeSetElasticity(ball.shape, 0.7);
}

static void wake()
{ }

static void do_world(cpFloat step)
{
  void process_events()
  {
    SDL_Event e;

    if(SDL_PollEvent(&e)) {
      switch(e.type)
      {
        case SDL_QUIT:
          endgame();
          break;
        default:
          break;
      }
    }
  }

  process_events();

  cpSpaceStep(space, step);
}

static void do_render()
{
  SDL_Surface* screen = scrget();
  if(nullp(screen))
    CRASH(SDL_GetError());

  void draw_ground()
  {
    SDL_Point pta = cpvSDL(
                        cpSegmentShapeGetA(ground.shape), screen, cpvzero);
    SDL_Point ptb = cpvSDL(
                        cpSegmentShapeGetB(ground.shape), screen, cpvzero);

    aalineColor(screen, pta.x, pta.y, ptb.x, ptb.y, 0xffffffff);
  }

  void draw_ball()
  {
    Sint16 radius = cpCircleShapeGetRadius(ball.shape);
    SDL_Point pos = cpvSDL(
                        cpBodyGetPos(ball.body), screen, cpvzero);
    aacircleColor(screen, pos.x, pos.y, radius, 0xffffffff);
  }

  draw_ground();
  draw_ball();
}

static void sleep()
{ }

static void deinit()
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


#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>

#include "entities/entities.h"
#include "engine/engine.h"
#include "states.h"

typedef struct EntityStack {
  Uint16 top;
  Entity* ents[];
} EntityStack;

cpSpace* space = NULL;
EntityStack* estack = NULL;
Uint16 pcount;

static EntityStack* mkentstack() {
  EntityStack* est = malloc(sizeof(EntityStack) + sizeof(Entity*) * 0x10000);

  for(int i = 0; i <= 0xffff; est->ents[i++] = NULL);

  return est;
}

static void delentstack(EntityStack* est) {
  for(int i = 0; i <= 0xffff; delentity(est->ents[i++]));
  free(est);
}

static void entpush(Entity* ent)
{
  if(nullp(estack->ents[estack->top++])) {
    estack->ents[estack->top] = ent;
  } else {
    entpush(ent);
  }
}

static void entkilldead()
{
  for(int i = 0; i <= 0xffff; i++) {
    Entity* ent = estack->ents[i];

    if(!nullp(ent)) {
      if(ent->life == 1) {
        delentity(ent);
        estack->ents[i] = NULL;
        pcount--;
      } else {
        ent->life--;
      }
    }
  }
}

// callbacks:

static void init()
{
  space = cpSpaceNew();
  cpSpaceSetGravity(space, cpv(0, -100));
  estack = mkentstack();
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
        case SDL_MOUSEBUTTONDOWN:
          break;
        default:
          break;
      }
    }
  }

  process_events();
  entpush(mkentity_particle(space, cpvzero, 
              cpv((ran_domo(1, 500) - 250) / 100.0,
                  (ran_domo(1, 500) - 250) / 100.0)));
  pcount++;
  cpSpaceStep(space, step);
  entkilldead();
}

static void do_render()
{
  void draw_particle(Entity* ent)
  {
    SDL_Point pt = cpvSDL(cpBodyGetPos(ent->body), scrget(), cpvzero);
    pixelColor(scrget(), pt.x, pt.y, ent->color);
  }

  void say_pcount()
  {
    static char str[64] = {0};

    snprintf(str, 64, "PARTICLES: %u", pcount);
    stringColor(scrget(), 10, scrget()->w - 30, str, 0xffffffff);
  }

  for(int i = 0; i <= 0xffff; i++) {
    if(!nullp(estack->ents[i])) {
      cpVect pos = cpBodyGetPos(estack->ents[i]->body);
      if(pos.x < scrget()->w / 2 && pos.y < scrget()->h / 2)
        draw_particle(estack->ents[i]);
    }
  }

  say_pcount();
}

static void sleep()
{ }

static void deinit()
{
  delentstack(estack);
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


NAME := goss
BUILD := debug

BINDIR := bin/
SRCDIR := src/
EXE := $(BINDIR)$(NAME)

SOURCES := $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(SOURCES:.c=.o)

SDL_CFLAGS = $(shell sdl-config --cflags)
SDL_LDFLAGS = $(shell sdl-config --libs)

ifeq ($(BUILD), debug)
  CFLAGS += $(SDL_CFLAGS) -O0 -Wall -pedantic -std=gnu11 -DDEBUG_MODE -Iinclude/
  LDFLAGS += $(SDL_LDFLAGS) -Wall -O0 -Llib/ -lchipmunk -lSDL_gfx

else ifeq ($(BUILD), release)
  CFLAGS += $(SDL_CFLAGS) -O3 -Wall -pedantic -std=gnu11 -DDEBUG_MODE -Iinclude/
  LDFLAGS += $(SDL_LDFLAGS) -Wall -O3 -Llib/ -static -lchipmunk -lSDL_gfx
endif

.PHONY: all clean cleandist

all: $(EXE)

$(EXE): $(OBJECTS) 
	$(CC) $(LDFLAGS) -o $@ $?

clean:
	@- $(RM) -v $(OBJECTS)

cleandist:
	@- $(RM) -v $(EXE)

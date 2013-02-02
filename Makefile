NAME := dame
BUILD := debug

BINDIR := bin/
SRCDIR := src/
EXE := $(BINDIR)$(NAME)

SOURCES := $(shell find $(SRCDIR) -type f -name '*.c')
OBJECTS = $(SOURCES:.c=.o)

SDL_CFLAGS = $(shell sdl-config --cflags)
SDL_LDFLAGS = $(shell sdl-config --libs)

ifeq ($(BUILD), debug)
  CFLAGS += $(SDL_CFLAGS) -g -O0 -Wall -std=gnu11 -DDEBUG_MODE -Iinclude/
  LDFLAGS += -Wl,-Bstatic -Llib/ -lchipmunk -lSDL_gfx \
	     -Wl,-Bdynamic -lm $(SDL_LDFLAGS)

else ifeq ($(BUILD), release)
  CFLAGS += $(SDL_CFLAGS) -O3 -Wall -std=gnu11 -DDEBUG_MODE -Iinclude/
  LDFLAGS += -Wl,-Bstatic -lchipmunk -lSDL_gfx \
	     -Wl,-Bdynamic $(SDL_LDFLAGS) 
endif

.PHONY: all clean cleandist

all: $(EXE)

$(EXE): $(OBJECTS) 
	$(CC) $? $(LDFLAGS) -o $@

clean:
	@- $(RM) -v $(OBJECTS)

cleandist:
	@- $(RM) -v $(EXE)

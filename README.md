# DAME
*distance and modular entities*

## Concept

DAME is a game about building, docking and flying various modular thingies
**in space**. Asteroid mining, planet destroying, trippy witchspace(ing) and
corovans robbing are the options too.

## Building

For Linux and MinGW you can just run `make` in this folder. It will invoke
CMake to configure and build executable in the *build* directory. You can also
pass following parameter to make:
+ **BUILD** - build type. Supported either `Debug` (the default) or `Release`.

Because of extensive usage of compiler extensions, for now DAME only builds
with *Clang*. It also needs linking against BlocksRuntime library on all
configurations with no native blocks support.

Current version: **0.0.922** <br />
Working on: making things work.


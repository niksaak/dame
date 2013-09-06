cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0001 NEW)
cmake_policy(SET CMP0008 NEW)
cmake_policy(SET CMP0015 NEW)

### ### ###
# Project

project(dame C)

if(NOT CMAKE_C_COMPILER_ID STREQUAL "Clang")
  message(SEND_ERROR
    "Clang is required to build the project, not ${CMAKE_C_COMPILER_ID}")
endif()

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/tools/CMakeModules/")

find_package(OpenGL REQUIRED)
find_package(glfw REQUIRED)
find_package(Check REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaults to Debug...")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Build type")
endif()

option(LINK_BLOCKS_RUNTIME
  "Link against BlockRuntime on targets with no builtin blocks support"
  YES)

# Chipmunk

set(BUILD_DEMOS OFF CACHE BOOL "Build chipmunk demos")
set(BUILD_SHARED OFF CACHE BOOL "Build shared chipmunk libraries")

set(CHIPMUNK_DIR "modules/chipmunk2d" CACHE PATH
  "Path to the Chipmunk2D library")

set(CHIPMUNK_INCLUDE_DIR "${CHIPMUNK_DIR}/include" CACHE INTERNAL
  "Chipmunk include/ directory")

add_subdirectory(${CHIPMUNK_DIR})

### ### ###
# Global includes and links

include_directories(${CHIPMUNK_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR}
  ${CHECK_INCLUDE_DIRS})

set(dame_LINKAGES "chipmunk_static m ${GLFW_LIBRARY} ${OPENGL_LIBRARIES}"
  CACHE INTERNAL "Libraries for linking")

# Base

get_filename_component(dame_MAIN_SOURCE "src/main.c" REALPATH)

file(GLOB_RECURSE dame_BASE_SOURCES "src/*.c")
list(REMOVE_ITEM dame_BASE_SOURCES ${dame_MAIN_SOURCE})
add_library(dame_base OBJECT ${dame_BASE_SOURCES})

# Exe

add_executable(dame ${dame_MAIN_SOURCE} $<TARGET_OBJECTS:dame_base>)
target_link_libraries(dame
  chipmunk_static m ${GLFW_LIBRARY} ${OPENGL_LIBRARIES})

if(LINK_BLOCKS_RUNTIME)
  find_library(BLOCKS_RUNTIME "BlocksRuntime")
  target_link_libraries(dame ${BLOCKS_RUNTIME})
endif()

# Tests

file(GLOB_RECURSE dame_TEST_SOURCES "test/*.c")
add_executable(checkall ${dame_TEST_SOURCES} $<TARGET_OBJECTS:dame_base>)
target_link_libraries(checkall
  chipmunk_static m ${GLFW_LIBRARY} ${OPENGL_LIBRARIES} ${CHECK_LIBRARIES})

if(LINK_BLOCKS_RUNTIME)
  find_library(BLOCKS_RUNTIME "BlocksRuntime")
  target_link_libraries(checkall ${BLOCKS_RUNTIME})
endif()

### ### ###
# Compiler

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu11 -fblocks")
  # enable warnings, compile as C11 with GNU extensions, enable blocks

set(CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS} -fno-caret-diagnostics -fno-color-diagnostics")
  # disable caret and colors

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math")


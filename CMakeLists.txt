cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0001 NEW)
cmake_policy(SET CMP0008 NEW)
cmake_policy(SET CMP0015 NEW)

# Project

project(dame C)

if(NOT CMAKE_C_COMPILER_ID STREQUAL "Clang")
  message(SEND_ERROR
    "Clang is required to build the project, not ${CMAKE_C_COMPILER_ID}")
endif()

find_package(OpenGL REQUIRED)
find_package(glfw REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaults to Debug...")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Build type")
endif()

set(LOCAL_INCLUDE_DIR "include" CACHE INTERNAL "Local include dir")
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

# Files

file(GLOB_RECURSE dame_SOURCES "src/*.c")
include_directories(${LOCAL_INCLUDE_DIR} ${CHIPMUNK_INCLUDE_DIR}
                    ${GLFW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

# Exe

set(EXE "bin/${CMAKE_PROJECT_NAME}" CACHE INTERNAL
  "Path for executable to be built")

make_directory("bin")
add_executable(${EXE} ${dame_SOURCES})

target_link_libraries(${EXE}
  chipmunk_static m ${GLFW_LIBRARY} ${OPENGL_LIBRARIES})
if(LINK_BLOCKS_RUNTIME)
  find_library(BLOCKS_RUNTIME "BlocksRuntime")
  target_link_libraries(${EXE} ${BLOCKS_RUNTIME})
endif()

# Compiler

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu11 -fblocks")
  # enable warnings, compile as C11 with GNU extensions, enable blocks

set(CMAKE_C_FLAGS
  "${CMAKE_C_FLAGS} -fno-caret-diagnostics -fno-color-diagnostics")
  # disable caret and colors

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math")


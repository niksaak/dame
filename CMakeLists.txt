cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0001 NEW)
cmake_policy(SET CMP0008 NEW)
cmake_policy(SET CMP0015 NEW)

# Project

project(dame)

find_package(OpenGL REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaults to Debug...")
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Files

file(GLOB dame_sources "src/*.c")

# Exe

include_directories(${OPENGL_INCLUDE_DIR})

make_directory("bin")
add_executable("bin/${CMAKE_PROJECT_NAME}" ${dame_sources})

if(CMAKE_BUILD_TYPE STREQUAL "Debug") # use own chipmunk when debugging
  link_directories(lib)
endif()
target_link_libraries("bin/${CMAKE_PROJECT_NAME}"
  chipmunk m glfw ${OPENGL_LIBRARIES})

# Compiler

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=c11")

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-diagnostics-show-caret")
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math")


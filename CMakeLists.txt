cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0001 NEW)
cmake_policy(SET CMP0008 NEW)
cmake_policy(SET CMP0015 NEW)

# Project

project(dame)

find_package(OpenGL REQUIRED)
find_package(glfw REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
  message(STATUS "Build type defaults to Debug...")
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
      "Build type")
endif()

set(local_include_dir "include")

# Chipmunk

set(chipmunk_dir "modules/chipmunk2d" CACHE PATH
    "Path to the Chipmunk2D library")
set(chipmunk_include_dir "${chipmunk_dir}/include")

add_subdirectory(${chipmunk_dir})

# Files

file(GLOB_RECURSE dame_sources "src/*.c")

# Exe

include_directories(${local_include_dir} ${chipmunk_include_dir}
                    ${GLFW_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

make_directory("bin")
add_executable("bin/${CMAKE_PROJECT_NAME}" ${dame_sources})

#if(CMAKE_BUILD_TYPE STREQUAL "Debug") # use own chipmunk when debugging
#  message(STATUS "Locating chipmunk in ${CMAKE_PREFIX_PATH}")
#  find_library(chipmunk "chipmunk" "${CMAKE_PREFIX_PATH}/lib")
#  message(STATUS "chipmunk path: ${chipmunk}")
#endif()
target_link_libraries("bin/${CMAKE_PROJECT_NAME}"
  chipmunk_static m ${GLFW_LIBRARY} ${OPENGL_LIBRARIES})

# Compiler

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu11")

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-diagnostics-show-caret")
endif()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -ffast-math")


cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0001 NEW)
cmake_policy(SET CMP0008 NEW)
cmake_policy(SET CMP0015 NEW)

project(DAME)

if(NOT ${CMAKE_BUILD_TYPE})
  set(CMAKE_BUILD_TYPE Debug)
endif()

find_package(SDL)

set(CMAKE_C_FLAGS "-Wall -std=gnu11")
set(CMAKE_C_FLAGS_DEBUG "-O0 -DDEBUG_MODE")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories("include" "src" ${SDL_INCLUDE_DIR})

file(GLOB DAME_source_engine "src/engine/*.c")
file(GLOB DAME_source_entities "src/entities/*.c")
file(GLOB DAME_source_states "src/state_*.c")
file(GLOB DAME_source_main "src/main.c")

link_directories(lib)

add_custom_target(DAME_engine DEPENDS ${DAME_source_engine})
add_custom_target(DAME_entities DEPENDS DAME_engine ${DAME_source_entities})
add_custom_target(DAME_states DEPENDS DAME_engine DAME_entities
  ${DAME_source_states})
add_custom_target(DAME_main DEPENDS DAME_engine DAME_entities DAME_states 
  ${DAME_source_main})

make_directory("bin")
add_executable("bin/${CMAKE_PROJECT_NAME}"
  ${DAME_source_engine} ${DAME_source_entities} ${DAME_source_states}
  ${DAME_source_main})
add_dependencies("bin/${CMAKE_PROJECT_NAME}"
  DAME_engine DAME_entities DAME_states DAME_main)

target_link_libraries("bin/${CMAKE_PROJECT_NAME}"
  -Wl,-Bstatic chipmunk SDL_gfx m
  -Wl,-Bdynamic ${SDL_LIBRARY})

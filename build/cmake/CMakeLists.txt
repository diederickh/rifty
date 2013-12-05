cmake_minimum_required(VERSION 2.8)

set(base_dir ${CMAKE_CURRENT_LIST_DIR}/../../)
set(extern_dir ${base_dir}/extern/)

set(CMAKE_INSTALL_PREFIX ${base_dir}/install/)

set(source_files 
  ${base_dir}/src/main.cpp
  ${base_dir}/src/Perlin.cpp
  ${base_dir}/src/Road.cpp
  ${base_dir}/src/Rifty.cpp
  ${base_dir}/src/Camera.cpp
  ${base_dir}/src/Particles.cpp
  ${base_dir}/src/room/Room.cpp
  ${base_dir}/src/room/RoomDrawer.cpp
  ${base_dir}/src/room/RoomEffect.cpp
  ${extern_dir}/src/GLXW/glxw.c
)

find_library(fr_corefoundation CoreFoundation)
find_library(fr_cocoa Cocoa)
find_library(fr_opengl OpenGL)
find_library(fr_iokit IOKit)

set(libraries
  ${extern_dir}/lib/libglfw3.a
  ${extern_dir}/lib/libpng16.a
  ${fr_corefoundation}
  ${fr_cocoa}
  ${fr_opengl}
  ${fr_iokit}  
  -lz
)

include_directories(
  ${extern_dir}/include
  ${base_dir}/src
)

add_executable(rifty ${source_files})

target_link_libraries(rifty ${libraries})

install(TARGETS rifty RUNTIME DESTINATION bin)
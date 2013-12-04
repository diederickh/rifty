cmake_minimum_required(VERSION 2.8)

set(base_dir ${CMAKE_CURRENT_LIST_DIR}/../../)
set(extern_dir ${base_dir}/extern/)

set(source_files 
  ${base_dir}/src/main.cpp
  ${extern_dir}/src/GLXW/glxw.c
)

find_library(fr_corefoundation CoreFoundation)
find_library(fr_cocoa Cocoa)
find_library(fr_opengl OpenGL)
find_library(fr_iokit IOKit)

set(libraries
  ${extern_dir}/lib/libglfw3.a
  ${fr_corefoundation}
  ${fr_cocoa}
  ${fr_opengl}
  ${fr_iokit}  
)

include_directories(
  ${extern_dir}/include
)

add_executable(rifty ${source_files})

target_link_libraries(rifty ${libraries})


  
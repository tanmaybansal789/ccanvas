cmake_minimum_required(VERSION 3.28)
project(ccanvas C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(external/glfw)
add_library(glad STATIC external/glad/src/glad.c)

include_directories(external/glfw/include)
include_directories(external/glad/include)
include_directories(include)

add_executable(ccanvas main.c

        include/ccanvas.h
        include/ccanvas_colours.h
        include/ccanvas_context.h
        include/ccanvas_defines.h
        include/ccanvas_shader.h
        include/ccanvas_window.h

        src/ccanvas_context.c
        src/ccanvas_shader.c
        src/ccanvas_window.c
        src/ccanvas_render.c
        include/ccanvas_render.h
)

target_link_libraries(ccanvas glfw glad)
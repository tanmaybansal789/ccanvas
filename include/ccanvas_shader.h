#ifndef CCANVAS_SHADER_H
#define CCANVAS_SHADER_H

#include "ccanvas_defines.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint ccanvas_shader_program_create(const char* vertex_path, const char* fragment_path);

#endif //CCANVAS_SHADER_H

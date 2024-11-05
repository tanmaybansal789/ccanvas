#include "ccanvas_shader.h"


static char* ccanvas_read_file_to_string(const char* path) {
    FILE* file = fopen(path, "r");
    if (file == NULL) {
        CCANVAS_ERR("Failed to open file: %s for reading", path);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* source = malloc(length + 1);
    if (source == NULL) {
        CCANVAS_ERR("Failed to allocate string to write file to");
        fclose(file);
        return NULL;
    }

    fread(source, 1, length, file);
    source[length] = '\0';

    fclose(file);
    return source;
}

static GLuint ccanvas_compile_shader(GLenum type, const char* path) {
    char* source = ccanvas_read_file_to_string(path);

    if (source == NULL) {
        return 0;
    }

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
    free(source);

    GLint compile_result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
    if (!compile_result) {
        char info_log[512];
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        CCANVAS_ERR("Shader: %s, compilation error: %s", path, info_log);
        return 0;
    }

    return shader;
}

GLuint ccanvas_shader_program_create(const char* vertex_path, const char* fragment_path) {
    CCANVAS_LOG("Creating shader from vertex: %s, and fragment: %s", vertex_path, fragment_path);

    GLuint vertex_shader = ccanvas_compile_shader(GL_VERTEX_SHADER, vertex_path);
    GLuint fragment_shader = ccanvas_compile_shader(GL_FRAGMENT_SHADER, fragment_path);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    GLint link_result;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &link_result);
    if (!link_result) {
        char info_log[512];
        glGetProgramInfoLog(shader_program, 512, NULL, info_log);
        CCANVAS_ERR("Program linking error: %s", info_log);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader_program;
}
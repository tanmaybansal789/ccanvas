#include "ccanvas_window.h"

static errno_t ccanvas_init_glfw() {
    static bool glfw_initialised = false;

    if (!glfw_initialised) {
        CCANVAS_LOG("Initialising GLFW");
        if (!glfwInit()) {
            CCANVAS_ERR("Failed to initialise GLFW");
            return -1;
        }
        glfw_initialised = true;
    }

    return 0;
}

static errno_t ccanvas_init_glad() {
    static bool glad_initialised = false;

    if (!glad_initialised) {
        CCANVAS_LOG("Initialising GLAD");
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            CCANVAS_ERR("Failed to initialise GLAD");
            return -1;
        }
        glad_initialised = true;
    }

    return 0;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

GLFWwindow* ccanvas_window_new(const char* title, int width, int height) {
    ccanvas_init_glfw();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        CCANVAS_ERR("Failed to create GLFW window");
    }

    glfwMakeContextCurrent(window);

    ccanvas_init_glad();

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}
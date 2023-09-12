#include <iostream>

#include <glad/glad.h>

#include "Window.h"

static GLFWwindow* create_window(unsigned int width, unsigned int height, const char* title);

Window::Window(unsigned int width, unsigned int height, const char* title)
{
    m_window = create_window(width, height, title);
    if (m_window == nullptr) {
        std::cerr << "Window.cpp: Failed to create a window\n";
    }
}

Window::~Window()
{
}

void Window::resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

bool Window::should_close() const
{
    return glfwWindowShouldClose(m_window);
}

GLFWwindow* Window::get_window() const
{
    return m_window;
}

static GLFWwindow* create_window(unsigned int width, unsigned int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfwGetPrimaryMonitor() makes it fullscreen
    // GLFWwindow* window = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to initialize GLFW\n";
        glfwTerminate();
        return nullptr;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return nullptr;
    }

    glViewport(0, 0, width, height);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return window;
}
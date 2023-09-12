#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

class Window
{
public:
    Window(unsigned int width = 1920, unsigned int height = 1080, const char* title = "Default title");
    ~Window();

    void resize(int width, int height);
    
    bool should_close() const;
    
    GLFWwindow* get_window() const;

private:
    GLFWwindow* m_window = nullptr;
};

#endif
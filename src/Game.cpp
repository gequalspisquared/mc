#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Game.h"

// static GLFWwindow* create
static void initialize_callbacks(Game* game);

Game::Game()
{
    m_window = Window(m_window_width, m_window_height, "Guh");
    initialize_callbacks(this);
    // glfwSetWindowUserPointer(m_window.get_window(), this);

    // glfwSetKeyCallback(m_window.get_window(), m_key_callback);
    

    // glfwSetFramebufferSizeCallback(m_window, m_framebuffer_size_callback);
    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetCursorPosCallback(m_window, m_mouse_callback);
    // glfwSetScrollCallback(m_window, m_scroll_callback);
    // glfwSetKeyCallback(m_window, m_key_callback);
}

Game::~Game()
{
    glfwTerminate();
}

int Game::run()
{
    while (!m_window.should_close()) {
        float current_frame = (float)glfwGetTime();
        m_delta_time = current_frame - m_last_frame;
        m_last_frame = current_frame;

        // TODO

        // handle input
        // update world
        // render
        
    }

    return 0;
}

GLFWwindow* Game::get_window() const
{
    return m_window.get_window();
}

void Game::process_screen_resize(int width, int height)
{
    m_window.resize(width, height);
}

void Game::process_mouse_input(double pos_x, double pos_y)
{

}

void Game::process_scroll_input(double offset_x, double offset_y)
{

}

void Game::process_keyboard_input(int key, int scancode, int action, int mods)
{

}

static void initialize_callbacks(Game* game)
{
    GLFWwindow* window = game->get_window();
    glfwSetWindowUserPointer(window, game);

    auto framebuffer_size_callback = [](GLFWwindow* w, int width, int height) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->process_screen_resize(width, height);
    };

    auto mouse_callback = [](GLFWwindow* w, double pos_x, double pos_y) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->process_mouse_input(pos_x, pos_y);
    };

    auto scroll_callback = [](GLFWwindow* w, double offset_x, double offset_y) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->process_scroll_input(offset_x, offset_y);
    };

    auto key_callback = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->process_keyboard_input(key, scancode, action, mods);
    };

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
}
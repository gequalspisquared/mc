#pragma once

#ifndef GAME_H
#define GAME_H

#include <GLFW/glfw3.h>

#include "Window.h"
#include "Player.h"

class Game
{
public:
    Game();
    ~Game();

    int run();
    
    GLFWwindow* get_window() const;

    // GLFW callback wrappers
    void process_screen_resize(int width, int height);
    void process_mouse_input(double pos_x, double pos_y);
    void process_scroll_input(double offset_x, double offset_y);
    void process_keyboard_input(int key, int scancode, int action, int mods);

private:
    Window m_window;

    Player m_player;
    
    unsigned int m_window_width  = 2560;
    unsigned int m_window_height = 1440;

    float m_delta_time = 0.0f;
    float m_last_frame = 0.0f;

};

#endif
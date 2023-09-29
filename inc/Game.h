#pragma once

#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>

#include "Window.h"
#include "Player.h"
#include "Chunk.h"
// #include "World.h"

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


    Chunk m_chunk;
    Shader m_chunk_shader = Shader(RESOURCES_PATH "shaders/chunk.vert", RESOURCES_PATH "shaders/chunk.frag");

    // World m_world;
    
    unsigned int m_window_width  = 2560;
    unsigned int m_window_height = 1440;
    unsigned int m_texture_atlas;

    float m_delta_time = 0.0f;
    float m_last_frame = 0.0f;

    void draw() const;
};

#endif
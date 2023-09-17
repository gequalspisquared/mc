#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <map>

#include <glm/glm.hpp>

#include "Camera.h"

enum Keys
{
    W,
    A,
    S,
    D,
    SPACE,
    LEFT_CONTROL
};

class Player
{
public:
    Player();
    ~Player();

    void process_keyboard_input(int key, int scancode, int action, int mods, float delta_time);
    void process_mouse_input(float offset_x, float offset_y, GLboolean constrain_pitch = true);
    void process_keymap(float delta_time);

    glm::mat4 get_view_matrix() const;
    glm::vec3 get_position() const;

private:
    Camera m_camera;
    std::map<Keys, bool> m_keys_pressed;

    // glm::vec3 position;
};

#endif
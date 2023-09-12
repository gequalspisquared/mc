#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>

#include "Camera.h"

class Player
{
public:
    Player();
    ~Player();

    void process_keyboard_input(int key, int scancode, int action, int mods, float delta_time);
    void process_mouse_input(float offset_x, float offset_y, GLboolean constrain_pitch = true);

    glm::mat4 get_view_matrix() const;
    glm::vec3 get_position() const;

private:
    Camera m_camera;

    // glm::vec3 position;
};

#endif
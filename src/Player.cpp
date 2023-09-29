#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Player.h"

enum PressableKeys
{
    W,
    A,
    S,
    D,
    SPACE,
    LEFT_CONTROL
};

static std::map<PressableKeys, bool> keys_pressed;

Player::Player()
{
}

Player::~Player()
{
}

void Player::process_keyboard_input(int key, int scancode, int action, int mods, float delta_time)
{
    if (key == GLFW_KEY_W) {
        if (action == GLFW_PRESS) {
            keys_pressed[W] = true;
        } else if (action == GLFW_RELEASE) {
            keys_pressed[W] = false;
        }
    }
    if (key == GLFW_KEY_A) {
        if (action == GLFW_PRESS) {
            keys_pressed[A] = true;
        } else if (action == GLFW_RELEASE) {
            keys_pressed[A] = false;
        }
    }
    if (key == GLFW_KEY_S) {
        if (action == GLFW_PRESS) {
            keys_pressed[S] = true;
        } else if (action == GLFW_RELEASE) {
            keys_pressed[S] = false;
        }
    }
    if (key == GLFW_KEY_D) {
        if (action == GLFW_PRESS) {
            keys_pressed[D] = true;
        } else if (action == GLFW_RELEASE) {
            keys_pressed[D] = false;
        }
    }
    if (key == GLFW_KEY_SPACE) {
        if (action == GLFW_PRESS) {
            keys_pressed[SPACE] = true;
        } else if (action == GLFW_RELEASE) {
            keys_pressed[SPACE] = false;
        }
    }
    if (key == GLFW_KEY_LEFT_CONTROL) {
        if (action == GLFW_PRESS) {
            keys_pressed[LEFT_CONTROL] = true;
        } else if (action == GLFW_RELEASE) {
            keys_pressed[LEFT_CONTROL] = false;
        }
    }
}

void Player::process_mouse_input(float offset_x, float offset_y, GLboolean constrain_pitch)
{
    m_camera.process_mouse_movement(offset_x, offset_y, constrain_pitch);
}

void Player::process_keymap(float delta_time)
{
    if (keys_pressed[W] == true) {
        m_camera.process_keyboard(FORWARD, delta_time);
    }
    if (keys_pressed[A] == true) {
        m_camera.process_keyboard(LEFT, delta_time);
    }
    if (keys_pressed[S] == true) {
        m_camera.process_keyboard(BACKWARD, delta_time);
    }
    if (keys_pressed[D] == true) {
        m_camera.process_keyboard(RIGHT, delta_time);
    }
    if (keys_pressed[SPACE] == true) {
        m_camera.process_keyboard(JUMP, delta_time);
    }
    if (keys_pressed[LEFT_CONTROL] == true) {
        m_camera.process_keyboard(CROUCH, delta_time);
    }
}

glm::mat4 Player::get_view_matrix() const
{
    return m_camera.get_view_matrix();
}

glm::vec3 Player::get_position() const
{
    return m_camera.get_position();
}
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::process_keyboard_input(int key, int scancode, int action, int mods, float delta_time)
{
    if (key == GLFW_KEY_W) {
        m_camera.process_keyboard(FORWARD, delta_time);
    }
    if (key == GLFW_KEY_A) {
        m_camera.process_keyboard(LEFT, delta_time);
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        m_camera.process_keyboard(BACKWARD, delta_time);
    }
    if (key == GLFW_KEY_D && action == GLFW_PRESS) {
        m_camera.process_keyboard(RIGHT, delta_time);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        m_camera.process_keyboard(JUMP, delta_time);
    }
    if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_PRESS) {
        m_camera.process_keyboard(CROUCH, delta_time);
    }
}

void Player::process_mouse_input(float offset_x, float offset_y, GLboolean constrain_pitch)
{
    m_camera.process_mouse_movement(offset_x, offset_y, constrain_pitch);
}

glm::mat4 Player::get_view_matrix() const
{
    return m_camera.get_view_matrix();
}

glm::vec3 Player::get_position() const
{
    return m_camera.get_position();
}
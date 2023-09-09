#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::process_keyboard_input(int key, int scancode, int action, int mods)
{
}

void Player::process_mouse_input(float offset_x, float offset_y, GLboolean constrain_pitch)
{
}

glm::mat4 Player::get_view_matrix() const
{
    return m_camera.get_view_matrix();
}

glm::vec3 Player::get_position() const
{
    return m_camera.get_position();
}
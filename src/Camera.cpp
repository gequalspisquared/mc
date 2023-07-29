#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

extern const float YAW   = -90.0f;
extern const float PITCH =  0.0f;
const float SPEED        =  2.5f;
const float SENSITIVITY  =  0.1f;
const float ZOOM         =  70.0f;

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_position(position)
    , m_up(up)
    , m_world_up(m_up)
    , m_yaw(yaw)
    , m_pitch(pitch)
    , m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    , m_speed(SPEED)
    , m_sensitivity(SENSITIVITY)
    , m_zoom(ZOOM)
{
    update_camera_vectors();
}


Camera::Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch)
    : m_position(glm::vec3(pos_x, pos_y, pos_z))
    , m_up(glm::vec3(up_x, up_y, up_z))
    , m_world_up(m_up)
    , m_yaw(yaw)
    , m_pitch(pitch)
    , m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    , m_speed(SPEED)
    , m_sensitivity(SENSITIVITY)
    , m_zoom(ZOOM)
{
    update_camera_vectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::get_view_matrix() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::process_keyboard(CameraMovement direction, float delta_time)
{
    float speed = m_speed * delta_time;
    if (direction == FORWARD) {
        m_position += m_front * speed;
    }
    if (direction == LEFT) {
        m_position -= m_right * speed;
    }
    if (direction == BACKWARD) {
        m_position -= m_front * speed;
    }
    if (direction == RIGHT) {
        m_position += m_right * speed;
    }
    if (direction == JUMP) {
        m_position += m_world_up * speed;
    }
    if (direction == CROUCH) {
        m_position -= m_world_up * speed;
    }
}

void Camera::process_mouse_movement(float offset_x, float offset_y, GLboolean constrain_pitch)
{
    offset_x *= m_sensitivity;
    offset_y *= m_sensitivity;

    m_yaw += offset_x;
    m_pitch += offset_y;

    if (constrain_pitch) {
        if (m_pitch > 89.0f) {
            m_pitch = 89.0f;
        } else if (m_pitch < -89.0f) {
            m_pitch = -89.0f;
        }
    }

    update_camera_vectors();
}

void Camera::process_mouse_scroll(float offset_y)
{
    m_zoom -= offset_y;
    if (m_zoom < 1.0f) {
        m_zoom = 1.0f;
    } else if (m_zoom > 100.0f) {
        m_zoom = 100.0f;
    }
}

void Camera::update_camera_vectors()
{
    glm::vec3 front = glm::vec3(
        cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
        sin(glm::radians(m_pitch)),
        sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))
    );

    m_front = glm::normalize(front);
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up    = glm::normalize(glm::cross(m_right, m_front));
}
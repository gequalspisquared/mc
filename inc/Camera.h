#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>

enum CameraMovement 
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    JUMP,
    CROUCH,
};

extern const float YAW;
extern const float PITCH;

class Camera
{
public: 
    Camera(glm::vec3 position = glm::vec3(20.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    Camera(float pos_x, float pos_y, float pos_z, float up_x, float up_y, float up_z, float yaw, float pitch);
    ~Camera();

    glm::mat4 get_view_matrix() const;
    glm::vec3 get_position() const;

    void process_keyboard(CameraMovement direction, float delta_time);
    void process_mouse_movement(float offset_x, float offset_y, GLboolean constrain_pitch = true);
    void process_mouse_scroll(float offset_y);

private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;
    float m_yaw;
    float m_pitch;
    // float m_roll;
    float m_speed;
    float m_sensitivity;
    float m_zoom;

    void update_camera_vectors();
};

#endif
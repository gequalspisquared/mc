#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in int voxel_id;
layout (location = 2) in int face_id;

out vec3 pos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() 
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    pos = position;
}
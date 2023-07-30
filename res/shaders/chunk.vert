#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in int voxel_id;
layout (location = 2) in int face_id;

// in vec2 texture_coordinates;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

// out vec3 pos;
// out int voxel_id;
out vec2 uv;

const vec2 uv_coords[4] = vec2[4](
    vec2(0, 0), vec2(0, 1),
    vec2(1, 0), vec2(1, 1)
);

const int uv_indices[6] = int[6](
    0, 3, 1, 0, 2, 3
    // 1, 0, 2, 1, 2, 3,
    // 0, 2, 3, 1, 0, 3
    // 3, 0, 2, 3, 1, 0 // original 
    // 0, 1, 3, 2, 0, 3
    // 3, 0, 3, 0, 1, 3
    // 3, 2, 0, 3, 1, 0
    // 2, 0, 1, 2, 3, 0
);

void main() 
{
    // int uv_index = gl_VertexID % 6 + (face_id & 1) * 6;
    int uv_index = gl_VertexID % 6;
    uv = uv_coords[uv_indices[uv_index]];
    gl_Position = projection * view * model * vec4(position, 1.0);
    // pos = position;
}
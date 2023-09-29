#version 460 core

layout (location = 0) in ivec3 position;
layout (location = 1) in int voxel_id;
layout (location = 2) in int face_id;

// uniform ivec3 world_position;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 uv;

const vec2 uv_coords[4] = vec2[4](
    vec2(0, 0), vec2(0, 1),
    vec2(1, 0), vec2(1, 1)
);

const int uv_indices[6] = int[6](
    0, 3, 1, 0, 2, 3
);

const int num_rows = 16;

vec2 id_to_uv_offset(int id) 
{
    // id = id - 1;
    int offset_x = (id - 1)%num_rows;
    int offset_y = num_rows - (id - 1)/num_rows - 1;

    if (id == 1) { // grass block
        if (face_id == 5) {
            offset_x = offset_x + 2;
        } else if (face_id > 0) {
            offset_x = offset_x + 3;
        }
    }

    return vec2(offset_x, offset_y);
    // if (id == 1) {
    //     return vec2(1, 15);
    // }
    // else if (id == 2) {
    //     return vec2(4, 15);
    // }
    // return vec2(0, 0);
}

void main() 
{
    int uv_index = gl_VertexID % 6;

    uv = uv_coords[uv_indices[uv_index]];
    uv = uv + id_to_uv_offset(voxel_id);
    uv = uv / num_rows;

    // gl_Position = projection * view * model * vec4(world_position + position, 1.0);
    gl_Position = projection * view * model * vec4(position, 1.0);
}
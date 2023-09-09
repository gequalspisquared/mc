#pragma once

#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>
#include <vector>

#include "Shader.h"

const unsigned int CHUNK_WIDTH  = 16;
const unsigned int CHUNK_HEIGHT = 16;
const unsigned int CHUNK_VOLUME = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_HEIGHT;

// enum class Face
// {
//     top,
//     front,
//     left,
//     back,
//     right,
//     bottom
// };

typedef uint8_t voxel_id;

struct Vertex 
{
    uint8_t x;
    uint8_t y;
    uint8_t z;
    voxel_id vox_id;
    uint8_t face_id;
};

struct WorldPosition
{
    int x = 0;
    int y = 0;
    int z = 0;
};

class Chunk
{
public:
    Chunk(WorldPosition world_position = WorldPosition());
    ~Chunk();

    void draw(const Shader& shader) const;

private:
    voxel_id m_voxels[CHUNK_VOLUME] = {}; // array of voxel ids
    // uint8_t m_vertex_data[CHUNK_VOLUME * 18 * 10] = {};
    std::vector<uint8_t> m_vertex_data;
    size_t m_num_triangles = 0;
    unsigned int m_vao;
    WorldPosition m_world_position;

    void build_mesh();
    void build_voxels();
    void create_vao(unsigned int& VAO);
    size_t add_data(size_t index, Vertex vertices[6]);
    bool is_void(int x, int y, int z) const;
};

#endif
#pragma once

#ifndef CHUNK_H
#define CHUNK_H

#include <cstdint>
#include <vector>

#include "Shader.h"

const unsigned int CHUNK_WIDTH  = 16;
const unsigned int CHUNK_HEIGHT = 4;
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

struct Vertex 
{
    uint8_t x;
    uint8_t y;
    uint8_t z;
    uint8_t voxel_id;
    uint8_t face_id;
};

class Chunk
{
public:
    Chunk();
    ~Chunk();

    void draw(const Shader& shader) const;

private:
    uint8_t m_voxels[CHUNK_VOLUME] = {}; // array of voxel ids
    // uint8_t m_vertex_data[CHUNK_VOLUME * 18 * 10] = {};
    std::vector<uint8_t> m_vertex_data;
    size_t m_num_triangles = 0;
    unsigned int m_vao;

    void build_mesh();
    void build_voxels();
    void create_vao(unsigned int& VAO);
    size_t add_data(size_t index, Vertex vertices[6]);
    bool is_void(int x, int y, int z) const;
};

#endif
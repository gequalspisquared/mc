#pragma once

#ifndef CHUNK_H
#define CHUNK_H

#include <vector>

#include "Shader.h"

class World;

const unsigned int CHUNK_WIDTH  = 16; // cubic chunks, length of each side
const unsigned int CHUNK_VOLUME = CHUNK_WIDTH * CHUNK_WIDTH * CHUNK_WIDTH; // dx, dy, dz

typedef uint8_t voxel_id_t;
typedef uint8_t face_id_t;

struct Vertex
{
    uint8_t x;
    uint8_t y;
    uint8_t z;
    voxel_id_t voxel_id;
    face_id_t face_id;
};

struct WorldPosition
{
    int x;
    int y;
    int z;
};

class Chunk
{
public:
    Chunk(const World* world, const WorldPosition& world_position);
    ~Chunk();

    void draw(const Shader& shader) const;
    void update();

    WorldPosition get_world_position() const;

    voxel_id_t get_voxel_id(size_t voxel_index) const;

private:
    voxel_id_t m_voxel_ids[CHUNK_VOLUME] = {}; // id corresponds to a block type

    std::vector<uint8_t> m_vertex_data;

    unsigned int m_vao; // where buffer data is stored in gpu

    size_t m_num_triangles = 0;

    WorldPosition m_world_position;

    const World* m_world;

    void build_voxels();
    void build_mesh();
    void create_vao();
};

#endif
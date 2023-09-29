#pragma once

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <memory>
#include <optional>

#include "Chunk.h"
#include "Shader.h"

// Size of world in chunks
const size_t WORLD_WIDTH  = 3; // can be thought of as render distance
const size_t WORLD_HEIGHT = 1;

class World
{
public:
    World();
    ~World();

    void draw() const;

    std::shared_ptr<Chunk> get_chunk_from_world_position(const WorldPosition& chunk_world_position) const;

private:
    std::vector<std::shared_ptr<Chunk>> m_chunks;
    Shader m_chunk_shader = Shader(RESOURCES_PATH "shaders/chunk.vert", RESOURCES_PATH "shaders/chunk.frag");

    std::optional<size_t> get_chunk_index_from_position(const WorldPosition& chunk_world_position) const;
};

#endif
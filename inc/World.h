#pragma once

#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"
#include "Shader.h"

// size of world in chunks
// can also be thought of as 'render distance'
const unsigned int WORLD_WIDTH = 3;
const unsigned int WORLD_DEPTH = WORLD_WIDTH;
const unsigned int WORLD_AREA  = WORLD_DEPTH * WORLD_WIDTH;

class World
{
public:
    World();
    ~World();

    void draw() const;

    Shader chunk_shader = Shader(RESOURCES_PATH "shaders/chunk.vert", RESOURCES_PATH "shaders/chunk.frag");

private:
    std::vector<Chunk> m_chunks;
};

#endif
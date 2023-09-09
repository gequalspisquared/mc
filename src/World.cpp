#include <iostream>

#include "World.h"
#include "Player.h"

World::World()
{
    m_chunks.resize(WORLD_AREA);
    for (size_t x = 0; x < WORLD_WIDTH; x++) {
        for (size_t z = 0; z < WORLD_DEPTH; z++) {
            std::cout << "Building chunk " << x*WORLD_WIDTH + z << "\n";
            WorldPosition world_position = {x, 0, z};
            m_chunks[x*WORLD_WIDTH + z] = Chunk(world_position);
        }
    }
}

World::~World()
{
}

void World::draw() const
{
    for (size_t x = 0; x < WORLD_WIDTH; x++) {
        for (size_t z = 0; z < WORLD_DEPTH; z++) {
            m_chunks[x*WORLD_WIDTH + z].draw(chunk_shader);
        }
    }
}
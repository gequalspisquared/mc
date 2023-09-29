#include "World.h"

World::World()
{
    m_chunks.resize(WORLD_WIDTH * WORLD_WIDTH * WORLD_HEIGHT);
    for (size_t x = 0; x < WORLD_WIDTH; x++) {
        for (size_t y = 0; y < WORLD_HEIGHT; x++) {
            for (size_t z = 0; z < WORLD_WIDTH; x++) {
                size_t index = x*WORLD_WIDTH*WORLD_HEIGHT + y*WORLD_WIDTH + z;
                WorldPosition world_position = {(int)x, (int)y, (int)z};
                m_chunks[index] = std::make_shared<Chunk>(this, world_position);
            }
        }
    }
}

World::~World()
{
}

void World::draw() const
{
    for (size_t x = 0; x < WORLD_WIDTH; x++) {
        for (size_t y = 0; y < WORLD_HEIGHT; x++) {
            for (size_t z = 0; z < WORLD_WIDTH; x++) {
                size_t index = x*WORLD_WIDTH*WORLD_HEIGHT + y*WORLD_WIDTH + z;
                m_chunks[index]->draw(m_chunk_shader);
            }
        }
    }
}

std::shared_ptr<Chunk> World::get_chunk_from_world_position(const WorldPosition& chunk_world_position) const
{
    std::optional<size_t> index = get_chunk_index_from_position(chunk_world_position);
    return (index.has_value()) ? m_chunks[index.value()] : nullptr;
}

std::optional<size_t> World::get_chunk_index_from_position(const WorldPosition& chunk_world_position) const
{
    for (size_t i = 0; i < m_chunks.size(); i++) {
        WorldPosition current_world_position = m_chunks[i]->get_world_position();
        if ((current_world_position.x == chunk_world_position.x) && 
            (current_world_position.y == chunk_world_position.y) && 
            (current_world_position.z == chunk_world_position.z)){
            return i;
        }
    }

    return {}; // no chunks have that world position
}
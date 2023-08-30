#pragma once

#ifndef WORLD_H
#define WORLD_H

#include "Chunk.h"

// size of world in chunks
const WORLD_WIDTH = 3;
const WORLD_DEPTH = WORLD_WIDTH;

class World
{
public:
    World();
    ~World();

    void draw() const;

private:

};

#endif
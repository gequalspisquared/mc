#pragma once

#ifndef QUAD_H
#define QUAD_H

#include "Shader.h"

enum class QuadDirection
{
    UP,
    FRONT,
    LEFT,
    BACK,
    RIGHT,
    DOWN
};

class Quad
{
public:
    Quad(QuadDirection direction, unsigned int id);
    ~Quad();

    draw(const Shader& shader) const;

private:
    const unsigned int m_id;
    
};

#endif
#pragma once

#ifndef CUBE_H
#define CUBE_H

#include "Shader.h"

struct CubeProperties
{
    int x;
    int y;
    int z;
};

class Cube 
{
public:
    Cube();
    ~Cube();

    void draw(const Shader shader) const;

private:
    size_t m_id;
    CubeProperties m_properties;    

    void create_vao(unsigned int& VAO);
}; 

#endif
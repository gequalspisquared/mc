#include "Cube.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static unsigned int CUBE_VAO;

static const float CUBE_VERTICES[] = 
{
     0.5,  0.5, -0.5, // texture coordinates
    -0.5,  0.5, -0.5,
    -0.5,  0.5,  0.5,
     0.5,  0.5,  0.5, 

     0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5
};

static const unsigned int CUBE_INDICES[] = {
    // TOP
    0, 2, 3,
    0, 1, 2,

    // FRONT
    0, 3, 7,
    0, 7, 4,

    // LEFT
    0, 4, 1,
    1, 4, 5,

    // BACK
    1, 5, 2,
    2, 5, 6,

    // RIGHT
    2, 6, 3,
    3, 6, 7,

    // DOWN
    7, 6, 4,
    6, 5, 4
};


Cube::Cube() : m_id(0), m_properties(CubeProperties{0, 0, 0})
{
    create_vao(CUBE_VAO);
}

Cube::~Cube()
{
}

void Cube::draw(const Shader shader) const
{
    std::cout << "Drawing\n";
    glBindVertexArray(CUBE_VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Cube::create_vao(unsigned int& VAO)
{
    static bool ran = false;

    if (ran) return;
    unsigned int VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_VERTICES), CUBE_VERTICES, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(CUBE_INDICES), CUBE_INDICES, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    // // color attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);
    // texture coord attribute
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    
    ran = true;
}
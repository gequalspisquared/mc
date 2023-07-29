#include "Chunk.h"

Chunk::Chunk()
{
    m_num_triangles = 0;
    m_vertex_data.resize(CHUNK_VOLUME * 18 * 10);
    build_voxels();
    build_mesh();

    std::cout << m_num_triangles << "\n";
    // for (size_t i = 0; i < 1 * 18; i++) {
    //     std::cout << "x: " << (int)m_vertex_data[5*i]  << " "
    //               << "y: " << (int)m_vertex_data[5*i + 1] << " "
    //               << "z: " << (int)m_vertex_data[5*i + 2] << " "
    //               << "vid: " << (int)m_vertex_data[5*i + 3] << " "
    //               << "fid: " << (int)m_vertex_data[5*i + 4] << "\n";
    // }

    create_vao(m_vao);
    std::cout << "Built chunk\n";
}

Chunk::~Chunk()
{
    // delete[](m_vertex_data);
}

void Chunk::draw(const Shader& shader) const
{
    std::cout << "Drawing chunk\n";
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, m_num_triangles * 3);
}

void Chunk::build_mesh() 
{
    std::cout << "Building mesh\n";
    size_t index = 0;
    size_t num_triangles = 0;
    m_num_triangles = 0;

    for (uint8_t x = 0; x < CHUNK_WIDTH; x++) {
        for (uint8_t y = 0; y < CHUNK_HEIGHT; y++) {
            for (uint8_t z = 0; z < CHUNK_WIDTH; z++) {
                uint8_t voxel_id = m_voxels[x + y*CHUNK_HEIGHT + z*CHUNK_WIDTH];
                std::cout << (int)voxel_id << "\n";
                if (!voxel_id) {
                    continue;
                }

                // Vertex vertices[6];

                // top
                if (is_void(x, y + 1, z)) {
                    Vertex v0 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 1), uint8_t(z + 0), voxel_id, (uint8_t)0};
                    Vertex v1 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 1), uint8_t(z + 0), voxel_id, (uint8_t)0};
                    Vertex v2 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 1), uint8_t(z + 1), voxel_id, (uint8_t)0};
                    Vertex v3 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 1), uint8_t(z + 1), voxel_id, (uint8_t)0};
                    Vertex vertices[] = {v0, v3, v2, v0, v2, v1};
                    index = add_data(index, vertices);
                    num_triangles += 2;
                }

                // front
                if (is_void(x + 1, y, z)) {
                    Vertex v0 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 1), uint8_t(z + 0), voxel_id, 1};
                    Vertex v1 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 0), uint8_t(z + 0), voxel_id, 1};
                    Vertex v2 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 0), uint8_t(z + 1), voxel_id, 1};
                    Vertex v3 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 1), uint8_t(z + 1), voxel_id, 1};
                    Vertex vertices[] = {v0, v3, v2, v0, v2, v1};
                    index = add_data(index, vertices);
                    num_triangles += 2;
                }

                // left
                if (is_void(x, y, z - 1)) {
                    Vertex v0 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 1), uint8_t(z + 0), voxel_id, 2};
                    Vertex v1 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 0), uint8_t(z + 0), voxel_id, 2};
                    Vertex v2 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 0), uint8_t(z + 0), voxel_id, 2};
                    Vertex v3 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 1), uint8_t(z + 0), voxel_id, 2};
                    Vertex vertices[] = {v0, v3, v2, v0, v2, v1};
                    index = add_data(index, vertices);
                    num_triangles += 2;
                }

                // back
                if (is_void(x - 1, y, z)) {
                    Vertex v0 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 1), uint8_t(z + 0), voxel_id, 3};
                    Vertex v1 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 0), uint8_t(z + 0), voxel_id, 3};
                    Vertex v2 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 0), uint8_t(z + 1), voxel_id, 3};
                    Vertex v3 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 1), uint8_t(z + 1), voxel_id, 3};
                    Vertex vertices[] = {v0, v3, v2, v0, v2, v1};
                    index = add_data(index, vertices);
                    num_triangles += 2;
                }

                // right
                if (is_void(x, y, z + 1)) {
                    Vertex v0 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 1), uint8_t(z + 1), voxel_id, 4};
                    Vertex v1 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 0), uint8_t(z + 1), voxel_id, 4};
                    Vertex v2 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 0), uint8_t(z + 1), voxel_id, 4};
                    Vertex v3 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 1), uint8_t(z + 1), voxel_id, 4};
                    Vertex vertices[] = {v0, v3, v2, v0, v2, v1};
                    index = add_data(index, vertices);
                    num_triangles += 2;
                }

                // bottom 
                if (is_void(x, y - 1, z)) {
                    Vertex v0 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 0), uint8_t(z + 1), voxel_id, 5};
                    Vertex v1 = Vertex{(uint8_t)(x + 0), (uint8_t)(y + 0), uint8_t(z + 0), voxel_id, 5};
                    Vertex v2 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 0), uint8_t(z + 0), voxel_id, 5};
                    Vertex v3 = Vertex{(uint8_t)(x + 1), (uint8_t)(y + 0), uint8_t(z + 1), voxel_id, 5};
                    Vertex vertices[] = {v0, v3, v2, v0, v2, v1};
                    index = add_data(index, vertices);
                    num_triangles += 2;
                }
            }
        }
    }

    std::cout << "Index: " << index << "\n";
    std::cout << "Num triangles: " << num_triangles << "\n";
    m_num_triangles = num_triangles;
}

void Chunk::build_voxels()
{
    std::cout << "Building voxels\n";
    for (uint8_t x = 0; x < CHUNK_WIDTH; x++) {
        for (uint8_t y = 0; y < CHUNK_HEIGHT; y++) {
            for (uint8_t z = 0; z < CHUNK_WIDTH; z++) {
                // if (y == 1) continue;
                m_voxels[x*CHUNK_WIDTH*CHUNK_HEIGHT + y*CHUNK_WIDTH + z] = 1;
            }
        }
    }
}

size_t Chunk::add_data(size_t index, Vertex vertices[6])
{
    std::cout << "Adding data\n";
    for (size_t i = 0; i < 6; i++) {
        Vertex vertex = vertices[i];
        m_vertex_data[index++] = vertex.x;
        m_vertex_data[index++] = vertex.y;
        m_vertex_data[index++] = vertex.z;
        m_vertex_data[index++] = vertex.voxel_id;
        m_vertex_data[index++] = vertex.face_id;
    }
    return index;
}

bool Chunk::is_void(int x, int y, int z) const
{
    if (0 <= x && x < CHUNK_WIDTH && 0 <= y && y < CHUNK_HEIGHT && 0 <= z && z < CHUNK_WIDTH) {
        return !(m_voxels[x + y*CHUNK_HEIGHT + z*CHUNK_WIDTH]);
    }
    return true;
}

void Chunk::create_vao(unsigned int& VAO)
{
    std::cout << "Creating VAO\n";
    static bool ran = false;

    if (ran) return;
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_data.size() * sizeof(m_vertex_data[0]), &m_vertex_data[0], GL_STATIC_DRAW);

    // position attribute
    std::cout << "position" << "\n";
    glVertexAttribPointer(0, 3, GL_UNSIGNED_BYTE, GL_FALSE, 5 * sizeof(uint8_t), (void *)0);
    glEnableVertexAttribArray(0);
    // voxel id
    std::cout << "voxel" << "\n";
    glVertexAttribPointer(1, 1, GL_UNSIGNED_BYTE, GL_FALSE, 5 * sizeof(uint8_t), (void*)(3 * sizeof(uint8_t)));
    glEnableVertexAttribArray(1);
    // face id
    std::cout << "face" << "\n";
    glVertexAttribPointer(2, 1, GL_UNSIGNED_BYTE, GL_FALSE, 5 * sizeof(uint8_t), (void *)(4 * sizeof(uint8_t)));
    glEnableVertexAttribArray(2);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    std::cout << "bind buffer\n";
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    std::cout << "bind array\n";
    glBindVertexArray(0);
    
    std::cout << "created\n";
    ran = true;
}
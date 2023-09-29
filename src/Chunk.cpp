#include <glad/glad.h>

#include "Chunk.h"
#include "Blocks.h"

static size_t get_index(int x, int y, int z);
static size_t add_face_to_vertex_data(std::vector<uint8_t>& vertex_data, size_t voxel_index, voxel_id_t voxel_id, face_id_t face_id, size_t index);
static Vertex create_Vertex(int x, int y, int z, voxel_id_t voxel_id, face_id_t face_id);
static bool is_void(const Chunk* chunk, int x, int y, int z);

Chunk::Chunk(const World* world, const WorldPosition& world_position)
    : m_world(world)
    , m_world_position(world_position)
{
    m_vertex_data.resize(CHUNK_VOLUME * 5 * 18);

    build_voxels();
    update();
}

Chunk::~Chunk()
{
}

void Chunk::draw(const Shader& shader) const
{
    int x = m_world_position.x;
    int y = m_world_position.y;
    int z = m_world_position.z;
    size_t num_vertices = m_num_triangles * 3;

    shader.set_ivec3("world_position", x, y, z);
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)num_vertices);
}

void Chunk::update()
{
    build_mesh();
    create_vao();

    std::cout << "m_vertex_data[0-4]" << (int)m_vertex_data[0] << " "
                                      << (int)m_vertex_data[1] << " "
                                      << (int)m_vertex_data[2] << " "
                                      << (int)m_vertex_data[3] << " "
                                      << (int)m_vertex_data[4] << "\n";
}

voxel_id_t Chunk::get_voxel_id(size_t voxel_index) const
{
    return m_voxel_ids[voxel_index];
}

void Chunk::build_voxels()
{
    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_WIDTH; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                size_t index = get_index(x, y, z);

                if (y == 0) {
                    m_voxel_ids[index] = (uint8_t)Blocks::bedrock;
                    continue;
                }
                if (y < 11) {
                    m_voxel_ids[index] = (uint8_t)Blocks::stone;
                    continue;
                }
                if (y < 15) {
                    m_voxel_ids[index] = (uint8_t)Blocks::dirt;
                    continue;
                }
                if (y == 15) {
                    m_voxel_ids[index] = (uint8_t)Blocks::grass;
                    continue;
                }
                if (y > 15) {
                    continue;
                }
            }
        }
    }
}

void Chunk::build_mesh()
{
    size_t array_index = 0;
    m_num_triangles = 0;

    for (int x = 0; x < CHUNK_WIDTH; x++) {
        for (int y = 0; y < CHUNK_WIDTH; y++) {
            for (int z = 0; z < CHUNK_WIDTH; z++) {
                size_t voxel_index = get_index(x, y, z);
                voxel_id_t voxel_id = m_voxel_ids[voxel_index];

                if (!voxel_id) { // if block is air, don't create vertex data
                    continue;
                }

                if (is_void(this, x, y + 1, z)) { // top
                    array_index = add_face_to_vertex_data(m_vertex_data, voxel_index, voxel_id, 0, array_index);
                    m_num_triangles += 2;
                }
                if (is_void(this, x + 1, y, z)) { // front
                    array_index = add_face_to_vertex_data(m_vertex_data, voxel_index, voxel_id, 1, array_index);
                    m_num_triangles += 2;
                }
                if (is_void(this, x, y, z - 1)) { // left
                    array_index = add_face_to_vertex_data(m_vertex_data, voxel_index, voxel_id, 2, array_index);
                    m_num_triangles += 2;
                }
                if (is_void(this, x - 1, y, z)) { // back
                    array_index = add_face_to_vertex_data(m_vertex_data, voxel_index, voxel_id, 3, array_index);
                    m_num_triangles += 2;
                }
                if (is_void(this, x, y, z + 1)) { // right
                    array_index = add_face_to_vertex_data(m_vertex_data, voxel_index, voxel_id, 4, array_index);
                    m_num_triangles += 2;
                }
                if (is_void(this, x, y - 1, z)) { // bottom
                    array_index = add_face_to_vertex_data(m_vertex_data, voxel_index, voxel_id, 5, array_index);
                    m_num_triangles += 2;
                }
            }
        }
    }

    // m_num_triangles = 2 * array_index;
}

void Chunk::create_vao()
{
    std::cout << "Creating VAO\n";
    // static bool ran = false;

    // if (ran) return;
    unsigned int VBO;
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_data.size() * sizeof(m_vertex_data[0]), &m_vertex_data[0], GL_STATIC_DRAW);

    // position attribute
    std::cout << "position" << "\n";
    glVertexAttribIPointer(0, 3, GL_UNSIGNED_BYTE, 5 * sizeof(uint8_t), (void*)0);
    glEnableVertexAttribArray(0);
    // voxel id
    std::cout << "voxel" << "\n";
    glVertexAttribIPointer(1, 1, GL_UNSIGNED_BYTE, 5 * sizeof(uint8_t), (void*)(3 * sizeof(uint8_t)));
    glEnableVertexAttribArray(1);
    // face id
    std::cout << "face" << "\n";
    glVertexAttribIPointer(2, 1, GL_UNSIGNED_BYTE, 5 * sizeof(uint8_t), (void*)(4 * sizeof(uint8_t)));
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
    // ran = true;
}

static size_t get_index(int x, int y, int z)
{
    return x*CHUNK_WIDTH*CHUNK_WIDTH + y*CHUNK_WIDTH + z;
}

void get_coordinates_from_index(size_t index, int& x, int& y, int& z) 
{
    z = (int)index % CHUNK_WIDTH;
    y = ((int)index / CHUNK_WIDTH) % CHUNK_WIDTH;
    x = ((int)index / CHUNK_WIDTH / CHUNK_WIDTH) % CHUNK_WIDTH;
    std::cout << x << y << z << "\n";
}

static size_t add_face_to_vertex_data(std::vector<uint8_t>& vertex_data, size_t voxel_index, voxel_id_t voxel_id, face_id_t face_id, size_t index)
{
    Vertex v0, v1, v2, v3;
    int x, y, z;
    get_coordinates_from_index(voxel_index, x, y, z);

    if (face_id == 0) { // top face
        v0 = create_Vertex(x + 0, y + 1, z + 0, voxel_id, face_id);
        v1 = create_Vertex(x + 1, y + 1, z + 0, voxel_id, face_id);
        v2 = create_Vertex(x + 0, y + 1, z + 1, voxel_id, face_id);
        v3 = create_Vertex(x + 1, y + 1, z + 1, voxel_id, face_id);
    } else if (face_id == 1) { // front face
        v0 = create_Vertex(x + 1, y + 0, z + 1, voxel_id, face_id);
        v1 = create_Vertex(x + 1, y + 1, z + 1, voxel_id, face_id);
        v2 = create_Vertex(x + 1, y + 0, z + 0, voxel_id, face_id);
        v3 = create_Vertex(x + 1, y + 1, z + 0, voxel_id, face_id);
    } else if (face_id == 2) { // left face
        v0 = create_Vertex(x + 1, y + 0, z + 0, voxel_id, face_id);
        v1 = create_Vertex(x + 1, y + 1, z + 0, voxel_id, face_id);
        v2 = create_Vertex(x + 0, y + 0, z + 0, voxel_id, face_id);
        v3 = create_Vertex(x + 0, y + 1, z + 0, voxel_id, face_id);
    } else if (face_id == 3) { // back face
        v0 = create_Vertex(x + 0, y + 0, z + 0, voxel_id, face_id);
        v1 = create_Vertex(x + 0, y + 1, z + 0, voxel_id, face_id);
        v2 = create_Vertex(x + 0, y + 0, z + 1, voxel_id, face_id);
        v3 = create_Vertex(x + 0, y + 1, z + 1, voxel_id, face_id);
    } else if (face_id == 4) { // right face
        v0 = create_Vertex(x + 0, y + 0, z + 1, voxel_id, face_id);
        v1 = create_Vertex(x + 0, y + 1, z + 1, voxel_id, face_id);
        v2 = create_Vertex(x + 1, y + 0, z + 1, voxel_id, face_id);
        v3 = create_Vertex(x + 1, y + 1, z + 1, voxel_id, face_id);
    } else { // bottom face
        v0 = create_Vertex(x + 0, y + 0, z + 1, voxel_id, face_id);
        v1 = create_Vertex(x + 1, y + 0, z + 1, voxel_id, face_id);
        v2 = create_Vertex(x + 0, y + 0, z + 0, voxel_id, face_id);
        v3 = create_Vertex(x + 1, y + 0, z + 0, voxel_id, face_id);
    }

    Vertex vertices[] = {v0, v3, v1, v0, v2, v3};
    for (size_t i = 0; i < 6; i++) {
        Vertex vertex = vertices[i];
        vertex_data[index++] = vertex.x;
        vertex_data[index++] = vertex.y;
        vertex_data[index++] = vertex.z;
        vertex_data[index++] = vertex.voxel_id;
        vertex_data[index++] = vertex.face_id;
    }

    return index;
}

static Vertex create_Vertex(int x, int y, int z, voxel_id_t voxel_id, face_id_t face_id)
{
    return Vertex{(uint8_t)x, (uint8_t)y, (uint8_t)z, voxel_id, face_id};

}

static bool is_void(const Chunk* chunk, int x, int y, int z)
{
    size_t voxel_index = get_index(x, y, z);
    
    // inside
    if (0 <= x && x < CHUNK_WIDTH && 0 <= y && y < CHUNK_WIDTH && 0 <= z && z < CHUNK_WIDTH) {
        return !(chunk->get_voxel_id(voxel_index));
    }

    return true;
}
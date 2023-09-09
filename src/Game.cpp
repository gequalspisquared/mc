#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

#include "Game.h"

// static GLFWwindow* create
static void initialize_callbacks(Game* game);
static unsigned int initialize_texture_atlas();

Game::Game()
    : m_texture_atlas(initialize_texture_atlas())
{
    // m_window = Window(m_window_width, m_window_height, "Guh");
    initialize_callbacks(this);
    // glfwSetWindowUserPointer(m_window.get_window(), this);

    // glfwSetKeyCallback(m_window.get_window(), m_key_callback);
    

    // glfwSetFramebufferSizeCallback(m_window, m_framebuffer_size_callback);
    // glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glfwSetCursorPosCallback(m_window, m_mouse_callback);
    // glfwSetScrollCallback(m_window, m_scroll_callback);
    // glfwSetKeyCallback(m_window, m_key_callback);
}

Game::~Game()
{
    glfwTerminate();
}

int Game::run()
{
    while (!m_window.should_close()) {
        float current_frame = (float)glfwGetTime();
        m_delta_time = current_frame - m_last_frame;
        m_last_frame = current_frame;

        // TODO

        // handle input
        // update world
        // render

        draw();
    }

    return 0;
}

void Game::draw() const
{
    static const glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)m_window_width/(float)m_window_height, 0.1f, 100.0f);
    static const glm::mat4 model = glm::mat4(1.0f);

    static glm::mat4 view;
    view = m_player.get_view_matrix();

    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_world.chunk_shader.set_mat4("view", view);
    m_world.chunk_shader.set_mat4("projection", proj);
    m_world.chunk_shader.set_mat4("model", model);

    glBindTexture(GL_TEXTURE_2D, m_texture_atlas);
    m_world.draw();

    glBindVertexArray(0);

    glfwSwapBuffers(m_window.get_window());
    glfwPollEvents();
}

GLFWwindow* Game::get_window() const
{
    return m_window.get_window();
}

void Game::process_screen_resize(int width, int height)
{
    m_window.resize(width, height);
}

void Game::process_mouse_input(double pos_x, double pos_y)
{

}

void Game::process_scroll_input(double offset_x, double offset_y)
{

}

void Game::process_keyboard_input(int key, int scancode, int action, int mods)
{

}

static void initialize_callbacks(Game* game)
{
    GLFWwindow* window = game->get_window();
    glfwSetWindowUserPointer(window, game);

    auto framebuffer_size_callback = [](GLFWwindow* w, int width, int height) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->process_screen_resize(width, height);
    };

    auto mouse_callback = [](GLFWwindow* w, double pos_x, double pos_y) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->process_mouse_input(pos_x, pos_y);
    };

    auto scroll_callback = [](GLFWwindow* w, double offset_x, double offset_y) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->process_scroll_input(offset_x, offset_y);
    };

    auto key_callback = [](GLFWwindow* w, int key, int scancode, int action, int mods) {
        static_cast<Game*>(glfwGetWindowUserPointer(w))->process_keyboard_input(key, scancode, action, mods);
    };

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
}

static unsigned int initialize_texture_atlas()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    int width, height, nr_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(RESOURCES_PATH "textures/atlas.png", &width, &height, &nr_channels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "ERROR::TEXTURE::LOAD_FAILURE\n";
    }
    stbi_image_free(data);

    return texture;
}
#include "Shader.h"

static unsigned int create_shader(GLenum shader_type, const char* shader_path);
static unsigned int create_program(unsigned int vertex_shader, unsigned int fragment_shader) ;

Shader::Shader(const char* vertex_path, const char* fragment_path)
{
    unsigned int vertex_shader   = create_shader(GL_VERTEX_SHADER, vertex_path);
    unsigned int fragment_shader = create_shader(GL_FRAGMENT_SHADER, fragment_path);
    m_id = create_program(vertex_shader, fragment_shader);
}

Shader::~Shader()
{
}

void Shader::use() const
{
    glUseProgram(m_id);
}

void Shader::set_bool(const std::string& name, bool value) const 
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_int(const std::string& name, int value) const 
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_float(const std::string& name, float value) const 
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::set_vec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec2(const std::string &name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void Shader::set_vec3(const std::string &name, const glm::vec3 &value) const
{
    glUniform3fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec3(const std::string &name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void Shader::set_vec4(const std::string &name, const glm::vec4 &value) const
{
    glUniform4fv(glGetUniformLocation(m_id, name.c_str()), 1, &value[0]);
}

void Shader::set_vec4(const std::string &name, float x, float y, float z, float w) const
{
    glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void Shader::set_mat2(const std::string &name, const glm::mat2 &value) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::set_mat3(const std::string &name, const glm::mat3 &value) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::set_mat4(const std::string &name, const glm::mat4 &value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

static std::string extract_code(const char* shader_path)
{
    std::string code_str;
    std::ifstream code_file_stream;
    code_file_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        code_file_stream.open(shader_path);
        std::stringstream code_string_stream;
        code_string_stream << code_file_stream.rdbuf();
        code_file_stream.close();
        code_str = code_string_stream.str();
    } catch(std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_READ\nFILE: " << shader_path << "\n";
    }

    return code_str;
}

static unsigned int create_shader(GLenum shader_type, const char* shader_path)
{
    const std::string code = extract_code(shader_path); // cannot do extract.c_str()
    const char* shader_code = code.c_str();

    int success;
    char info_log[512];
    unsigned int shader_id = glCreateShader(shader_type);
    glShaderSource(shader_id, 1, &shader_code, NULL);
    glCompileShader(shader_id);
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        if (shader_type == GL_VERTEX_SHADER) {
            std::cerr << "ERROR::VERTEX::SHADER::COMPILATION_FAILED\n" << info_log << "\n";
        } else if (shader_type == GL_FRAGMENT_SHADER) {
            std::cerr << "ERROR::FRAGMENT::SHADER::COMPILATION_FAILED\n" << info_log << "\n";
        } else {
            std::cerr << "ERROR::UNKNOWN::SHADER::COMPILATION_FAILED\n" << info_log << "\n";
        }
    }

    return shader_id;
}

static unsigned int create_program(unsigned int vertex_shader, unsigned int fragment_shader) 
{
    int success;
    char info_log[512];

    unsigned int id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, info_log);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n" << info_log << "\n";
    }
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return id;
}
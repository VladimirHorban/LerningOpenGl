#include "Shader.hpp"

void Shader::load_shader_source() {
    std::stringstream buffer;

    // vertex shader
    std::ifstream vert_stream(m_vert_source);
    buffer << vert_stream.rdbuf();
    m_vert_source = buffer.str().c_str();

    // fragment shader
    std::ifstream frag_shader(m_frag_source);
    buffer << frag_shader.rdbuf();
    m_frag_source = buffer.str().c_str();
}

void Shader::check_shader_compile_status(GLuint shader) {
    GLint status;
    GLchar log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cout << log << std::endl;
    }
}

void Shader::create_shader() {
    // vertex shader
    m_vert_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vert_shader, 1, &m_vert_source, nullptr);
    glCompileShader(m_vert_shader);
    check_shader_compile_status(m_vert_shader);

    // fragment shader
    m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_frag_shader, 1, &m_frag_source, nullptr);
    glCompileShader(m_frag_shader);
    check_shader_compile_status(m_frag_shader);
}

void Shader::create_shader_program() {
    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, m_vert_shader);
    glAttachShader(m_shader_program, m_frag_shader);
    glLinkProgram(m_shader_program);

    GLint status;
    GLchar log[512];
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &status);
    if(!status) {
        glGetProgramInfoLog(m_shader_program, 512, nullptr, log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
    }
}

void Shader::cleanup() {
    glDeleteShader(m_vert_shader);
    glDeleteShader(m_frag_shader);
}

void Shader::use() {
    glUseProgram(m_shader_program);
}

GLuint Shader::get_shader_program() const {
    return m_shader_program;
}

Shader::Shader(const char* vert_shader_file, const char* frag_shader_file) : m_shader_program(0), m_vert_shader(0), m_frag_shader(0), m_vert_source(nullptr), m_frag_source(nullptr)
{
    load_shader_source();
    create_shader();
    create_shader_program();
    cleanup();
}
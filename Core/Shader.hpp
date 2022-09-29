#ifndef SHADER_HPP
#define SHADER_HPP

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
    Shader(const char* vert_shader_file, const char* frag_shader_file);

private:
    void load_shader_source();
    void create_shader();
    void create_shader_program();
    void cleanup();
    void check_shader_compile_status(GLuint shader);
    void use();
    GLuint get_shader_program() const;

    GLuint  m_shader_program;
    GLuint  m_vert_shader;
    GLuint  m_frag_shader;
    const GLchar* m_vert_source;
    const GLchar* m_frag_source;
};

#endif
#ifndef TEXTURE_HPP
#define TEXTURE_CPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <SOIL/SOIL.h>
#include "../../Core/Module.hpp"

class Textures : public Module
{
public:
    Textures(const char* name) : Module(name), width(800), height(600), text_w(0), text_h(0), m_window(nullptr),
                                        m_shader_program(0), m_vbo(0), m_ibo(0), m_vao(0), m_text_1(0), m_text_2(0) {}

    void run() override;

private:
    void init();
    void init_shaders();
    void init_buffers();
    void init_texture();

    unsigned char* load_image(const char* image_name);

    // window parameters
    int width;
    int height;

    // texture parameters
    int text_w;
    int text_h;

    GLFWwindow* m_window;
    GLuint      m_shader_program;

    GLuint m_vbo;
    GLuint m_ibo;
    GLuint m_vao;

    GLuint m_text_1;
    GLuint m_text_2;
};

#endif
#ifndef ADVANCED_TRIANGLE
#define ADVANCED_TRIANGLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "../../Core/Module.hpp"

class Advanced_Triangle : public Module
{
public:
    Advanced_Triangle(const char* name) : Module(name), width(800), height(600), m_window(nullptr),
                                        m_shader_program(0), m_vbo(0), m_vao(0) {}

    void run() override;

private:
    void init();
    void init_shaders();
    void init_buffers();

    int width;
    int height;

    GLFWwindow* m_window;
    GLuint      m_shader_program;

    GLuint m_vbo;
    GLuint m_vao;
};

#endif
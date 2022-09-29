#include "Texture.hpp"

namespace
{
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    static const GLfloat vertices[] = {
        -0.5, 0.5,  0.0,  1.0, 0.0, 0.0,  1.0, 1.0,
        -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  1.0, 0.0,
         0.5, -0.5, 0.0,  0.0, 0.0, 1.0,  0.0, 0.0,
         0.5, 0.5,  0.0,  1.0, 1.0, 0.0,  0.0, 1.0
    };

    static const GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    static const GLchar* vert_source = "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec3 color;\n"
    "uniform vec2 offset;\n"
    "out vec3 our_color;\n"
    "void main()\n"
    "{\n"
        "gl_Position = vec4(-position.x + offset.x, -position.y, position.z, 1.0);\n"
        "our_color = color;\n"
    "}\0";

    static const GLchar* frag_source = "#version 330 core\n"
    "in vec3 our_color;\n"
    "out vec4 color;\n"
    "void main()\n"
    "{\n"
        "color = vec4(our_color, 1.0);\n"
    "}\0";
};

void Textures::init() {
    std::cout << "Initializing..." << std::endl;

    if(glfwInit() != GLFW_TRUE) {
        std::cout << "Failed to initilize glfw!" << std::endl;
        std::cout << "Failed to initilize lesson " << get_module_name() << " !" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    std::cout << "glfw was successfully initialized!" << std::endl;

    m_window = glfwCreateWindow(width, height, "Texturing", nullptr, nullptr);
    if(!m_window) {
        std::cout << "Failed to create window!" << std::endl;
        std::cout << "Failed to initilize lesson " << get_module_name() << " !" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);

    std::cout << "window was successfully initialized!" << std::endl;

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        std::cout << "Failed to initialize GLEW!" << std::endl;
        std::cout << "Failed to initilize lesson " << get_module_name() << " !" << std::endl;
        glfwTerminate();
        return;
    }

    std::cout << "glew was successfully initialized!" << std::endl;

    glfwGetFramebufferSize(m_window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetKeyCallback(m_window, key_callback);

    std::cout << "Initializing complete!" << std::endl;
}

void Textures::init_shaders() {
    std::cout << "Initialize shaders..." << std::endl;

    GLint status;
    GLchar log[512];

    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert, 1, &vert_source, nullptr);
    glCompileShader(vert);
    glGetShaderiv(vert, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(vert, 512, nullptr, log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << log << std::endl;
    }

    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag, 1, &frag_source, nullptr);
    glCompileShader(frag);
    glGetShaderiv(frag, GL_COMPILE_STATUS, &status);
    if(!status) {
        glGetShaderInfoLog(frag, 512, nullptr, log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << log << std::endl;
    }

    m_shader_program = glCreateProgram();
    glAttachShader(m_shader_program, vert);
    glAttachShader(m_shader_program, frag);
    glLinkProgram(m_shader_program);
    glGetProgramiv(m_shader_program, GL_LINK_STATUS, &status);
    if(!status) {
        glGetProgramInfoLog(m_shader_program, 512, nullptr, log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << log << std::endl;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);

    std::cout << "Initializing complete!" << std::endl;
}

void Textures::init_buffers() {
    std::cout << "Initialize buffers..." << std::endl;

    // vbo
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ibo
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // vao
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    std::cout << "Initializing complete!" << std::endl;
}

unsigned char* Textures::load_image(const char* image_name) {
    return SOIL_load_image(image_name, &text_w, &text_h, 0, SOIL_LOAD_RGB);
}

void Textures::init_texture() {
    std::cout << "Initizlize texture..." << std::endl;

    glGenTextures(1, &m_text_1);
    glBindTexture(GL_TEXTURE_2D, m_text_1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    unsigned char* image = load_image("container.jpg");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, text_w, text_h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    glGenerateMipmap(GL_TEXTURE_2D);
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);

    std::cout << "Initializing complete!" << std::endl;
}

void Textures::run() {
    init();
    init_shaders();
    init_buffers();
    init_texture();

    while(!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(m_shader_program);

        GLint uniform_location = glGetUniformLocation(m_shader_program, "offset");
        glUniform2f(uniform_location, 0.5, 0.0);

        glBindVertexArray(m_vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(m_window);
    }

    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);

    glfwTerminate();
}
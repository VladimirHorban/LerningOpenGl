#ifndef HELLO_WINDOW_HPP
#define HELLO_WINDOW_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../Core/Module.hpp"

class Hello_Window final : public Module
{
public:
    Hello_Window(const char* name) : Module(name), width(800), height(600) {}

    void run() override;

private:
    int width;
    int height;
};

#endif
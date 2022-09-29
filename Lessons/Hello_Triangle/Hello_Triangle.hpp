#ifndef HELLO_TRIANGLE
#define HELLO_TRIANGLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../../Core/Module.hpp"

class Hello_Triangle final : public Module
{
public:
    Hello_Triangle(const char* name) : Module(name), width(800), height(600) {}

    void run() override;

private:
    int width;
    int height;
};

#endif
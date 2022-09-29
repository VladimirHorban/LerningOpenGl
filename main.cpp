#include "Core/Application.hpp"
#include "Lessons/Hello_Window/Hello_Window.hpp"
#include "Lessons/Hello_Triangle/Hello_Triangle.hpp"
#include "Lessons/Advanced_Triangle/Advanced_Triangle.hpp"
#include "Lessons/Texture/Texture.hpp"

static std::vector<Module*> lessons = {
    new Hello_Window("hello_window"),
    new Hello_Triangle("hello_triangle"),
    new Advanced_Triangle("advanced_triangle"),
    new Textures("texturing")
};

int main()
{
    Applciation app(&lessons);
    // run particular lesson
    app.run_module("texturing");
    return 0;
}
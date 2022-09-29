cmake_minimum_required(VERSION 3.2)

project(Core)

add_library(Core SHARED Application.hpp Module.hpp Shader.hpp Application.cpp Shader.cpp)

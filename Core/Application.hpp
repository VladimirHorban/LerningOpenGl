#ifndef CORE_HPP
#define CORE_HPP

#include <vector>
#include <string.h>
#include "Module.hpp"

class Applciation
{
public:
    Applciation(std::vector<Module*>* modules_vector) : modules(modules_vector) {}

    void run_module(const char* module_name) const;

private:
    std::vector<Module*>* modules;
};

#endif
#include "Application.hpp"

void Applciation::run_module(const char* module_name) const {
    for ( Module* it : *modules ) {
        if ( strcmp(it->get_module_name(), module_name) == 0 )
            it->run();
    }
}
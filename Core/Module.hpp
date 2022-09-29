#ifndef MODULE_HPP
#define MODULE_HPP

class Module
{
public:
    Module(const char* module_name) : name(module_name) {}
    const char* get_module_name() const {
        return name;
    }

    virtual void run() = 0;

private:
    const char* name;
};

#endif
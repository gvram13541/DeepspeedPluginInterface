#pragma once

#include "../plugin_interface.h"
#include <map>

// This is the header file defining plugin1 features inheriting plugin intreface
// In case if u want to add some other functions other than the one's specified in PluginInterface class you can add 
// by creating child class of trampoline class created in bindings.cpp

class Plugin1 : public PluginInterface {
public:
    Plugin1(const std::map<std::string, std::string>& args);

    int aio_read(const pybind11::args& args) override;
    int aio_write(const pybind11::args& args) override;
    int deepspeed_memcpy(const pybind11::args& args) override;
};
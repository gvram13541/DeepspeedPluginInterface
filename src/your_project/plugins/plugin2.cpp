#include "plugin_interface.h" 
#include <map> 
#include <iostream> 
using namespace std; 


class MyPlugin : public PluginInterface {
public:
    // Override the aio_read method from PluginInterface
    int aio_read(const pybind11::args& args) override {

        // need to add functionality here

        cout << "Performing reading through plugin2" << '\n';
        return 0; 
    }

    // Override the aio_write method from PluginInterface
    int aio_write(const pybind11::args& args) override {

        // need to add functionality here

        return 0; 
    }

    // Override the deepspeed_memcpy method from PluginInterface
    int deepspeed_memcpy(const pybind11::args& args) override {

        // need to add functionality here

        return 0; 
    }
};

// Define a function create_plugin that creates an instance of MyPlugin
extern "C" PluginInterface* create_plugin(const std::map<std::string, std::string>& args) {
    return new MyPlugin(); // Return a pointer to a new instance of MyPlugin common for both plugins
}

#include <torch/extension.h> // installed as binary files(using pip the code is not running every time)
#include <pybind11/pybind11.h> // installed as binary files(using pip the code is not running every time)
#include "plugin_interface.h" 
#include "plugin_loader.h" 

// Define a class PyPluginInterface(trampoline class) that inherits from PluginInterface
class PyPluginInterface : public PluginInterface {
public:
    using PluginInterface::PluginInterface; // Inherit constructors from PluginInterface

    // Override the aio_read method from PluginInterface
    int aio_read(const pybind11::args& args) override {
        // Call PYBIND11_OVERRIDE_PURE macro to override the method
        PYBIND11_OVERRIDE_PURE(
            int, 
            PluginInterface, 
            aio_read, 
            args 
        );
    }

    // Override the aio_write method from PluginInterface
    int aio_write(const pybind11::args& args) override {
        // Call PYBIND11_OVERRIDE_PURE macro to override the method
        PYBIND11_OVERRIDE_PURE(
            int, 
            PluginInterface, 
            aio_write, 
            args 
        );
    }

    // Override the deepspeed_memcpy method from PluginInterface
    int deepspeed_memcpy(const pybind11::args& args) override {
        // Call PYBIND11_OVERRIDE_PURE macro to override the method
        PYBIND11_OVERRIDE_PURE(
            int, 
            PluginInterface, 
            deepspeed_memcpy, 
            args 
        );
    }
};


PYBIND11_MODULE(_C, m) {
    // Bind the PyPluginInterface class to Python as 'PluginInterface'
    py::class_<PluginInterface, PyPluginInterface>(m, "PluginInterface")
        .def(py::init<>())
        .def("aio_read", &PluginInterface::aio_read) 
        .def("aio_write", &PluginInterface::aio_write) 
        .def("deepspeed_memcpy", &PluginInterface::deepspeed_memcpy); 

    // Bind the PluginLoader class to Python as 'PluginLoader'
    py::class_<PluginLoader>(m, "PluginLoader")
        .def(py::init<>()) 
        .def("register_plugin", &PluginLoader::register_plugin) // registers the plugins(in this case plugin1 or plugin2)
        .def("get_plugin", &PluginLoader::get_plugin, py::return_value_policy::reference); // returns the instance of registered plugin
}

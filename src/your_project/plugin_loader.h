#pragma once

#include <string>
#include <map>
#include <utility>
#include <dlfcn.h>
#include "plugin_interface.h"

class PluginLoader {
public:
    PluginLoader();
    ~PluginLoader();

    void register_plugin(const std::string& name, const std::string& library_path, const std::map<std::string, std::string>& args);
    PluginInterface* get_plugin(const std::string& name, const std::map<std::string, std::string>& args);

private:
    std::map<std::string, std::pair<void*, std::map<std::string, std::string>>> plugin_libraries_;
};
#include "plugin_loader.h"

// The functionalities of these functions are explained previously
// This methods here just register and returns the instace of the plugin registerd

PluginLoader::PluginLoader() = default;

PluginLoader::~PluginLoader() {
    for (const auto& [name, handle_and_args] : plugin_libraries_) {
        dlclose(handle_and_args.first);
    }
}

void PluginLoader::register_plugin(const std::string& name, const std::string& library_path, const std::map<std::string, std::string>& args) {
    void* handle = dlopen(library_path.c_str(), RTLD_LAZY);
    if (!handle) {
        throw std::runtime_error("Failed to load library: " + std::string(dlerror()));
    }
    plugin_libraries_[name] = std::make_pair(handle, args);
}

PluginInterface* PluginLoader::get_plugin(const std::string& name, const std::map<std::string, std::string>& args) {
    if (plugin_libraries_.count(name) == 0) {
        throw std::runtime_error("Plugin not found: " + name);
    }
    void* handle = plugin_libraries_[name].first;
    const auto& plugin_args = plugin_libraries_[name].second;
    std::map<std::string, std::string> merged_args(plugin_args);
    merged_args.insert(args.begin(), args.end());

    auto plugin_constructor = reinterpret_cast<PluginInterface* (*)(const std::map<std::string, std::string>&)>(dlsym(handle, "create_plugin"));
    if (!plugin_constructor) {
        throw std::runtime_error("Failed to find plugin constructor: " + std::string(dlerror()));
    }
    return plugin_constructor(merged_args);
}
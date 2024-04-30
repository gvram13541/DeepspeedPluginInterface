from your_project._C import PluginLoader

loader = PluginLoader()

plugin_path = "/home/yathin/plugin/libmyplugin.so"
loader.register_plugin("myplugin", plugin_path, {})

plugin_instance = loader.get_plugin("myplugin", {})

result = plugin_instance.aio_read()

print("Result of aio_read:", result)

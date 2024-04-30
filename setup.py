from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext
import os
import importlib.util
import sysconfig
import sys

# return pybind11 path
def get_pybind11_path():
    try:
        spec = importlib.util.find_spec("pybind11")
        if spec:
            return os.path.dirname(spec.origin)
    except ImportError:
        pass
    return None

pybind11_path = get_pybind11_path()

if not pybind11_path:
    print("Warning: pybind11 not found. Building may fail.")

python_include_path = sysconfig.get_path("include")
pytorch = "libtorch"

# taking from the user which plugin to be loaded
plugin_arg = None
for arg in sys.argv:
    if arg.startswith('--plugin='):
        plugin_arg = arg.split('=')[1]
        sys.argv.remove(arg)
        break

if plugin_arg == 'plugin1':
    plugin_sources = ['src/your_project/plugins/plugin1.cpp']
elif plugin_arg == 'plugin2':
    plugin_sources = ['src/your_project/plugins/plugin2.cpp']
else:
    print("Error: Invalid plugin specified. Please use --plugin=plugin1 or --plugin=plugin2.")
    sys.exit(1)

extension_module = Extension(
    'your_project._C',
    sources=[
        'src/your_project/bindings.cpp',
        'src/your_project/plugin_interface.cpp',
        'src/your_project/plugin_loader.cpp',
    ] + plugin_sources,
    include_dirs=['src/your_project', pybind11_path, python_include_path, "/usr/include/python3.10", "/home/yathin/plugin/libtorch/include", "/home/yathin/plugin/libtorch/include/torch/csrc/api/include"],
    language='c++',
    extra_compile_args=['-std=c++17','-g'],
    libraries=['torch', 'c10'],
    library_dirs=['/home/yathin/plugin/libtorch/lib'],
    extra_link_args=['-Wl,--no-as-needed','-v']
)

# creation of shared libraries(only one share library will be createdd)
def build_libmyplugin():
    if plugin_arg == 'plugin1':
        os.system('g++ -std=c++17 -fPIC -shared -o libmyplugin.so \
            -I/home/yathin/plugin/src/your_project \
            -I/home/yathin/plugin/libtorch/include \
            -I/home/yathin/plugin/pybind11/include \
            -I/usr/include/python3.10 \
            src/your_project/plugins/plugin1.cpp')
    elif plugin_arg == 'plugin2':
        os.system('g++ -std=c++17 -fPIC -shared -o libmyplugin.so \
            -I/home/yathin/plugin/src/your_project \
            -I/home/yathin/plugin/libtorch/include \
            -I/home/yathin/plugin/pybind11/include \
            -I/usr/include/python3.10 \
            src/your_project/plugins/plugin2.cpp')
    else:
        print("Error: Invalid plugin specified. Please use --plugin=plugin1 or --plugin=plugin2.")
        sys.exit(1)

class CustomBuildExt(build_ext):
    def run(self):
        super().run()
        self.execute(build_libmyplugin, ())
        register_plugin()

def register_plugin():
    from your_project._C import PluginLoader
    loader = PluginLoader()
    plugin_path = "/home/yathin/plugin/libmyplugin.so" 
    loader.register_plugin("myplugin", plugin_path, {})

setup(
    name='your_project',
    version='0.1',
    packages=['your_project', 'your_project.plugins'],  
    package_dir={'your_project': './src/your_project', 'your_project.plugins': './src/your_project/plugins'},  
    ext_modules=[extension_module],
    cmdclass={'build_ext': CustomBuildExt},
    install_lib={'src/your_project': register_plugin}  
)

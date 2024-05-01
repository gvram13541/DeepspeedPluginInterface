# Deepspeed Plugin Implementation

## Importing Required Libraries

For using torch extensions and the pybind11 module, we needed to download the binaries from the following sites:

- PyTorch: [Download here (Pre-cxx11 ABI)](https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-2.3.0%2Bcpu.zip)
- pybind11: We cloned it from the [pybind/pybind11 repository](https://github.com/pybind/pybind11.git)



## Folder Structure and Implementation Details

```
plugin/
├── setup.py
└── src/
    └── your_project/
        ├── __init__.py
        ├── bindings.cpp
        ├── plugin_interface.cpp
        ├── plugin_loader.cpp
        ├── _C.py (this file will be generated during the build process)
        └── plugins/
            ├── __init__.py
            ├── plugin1.h
            ├── plugin1.cpp
            └── ... (other plugin source files if any)
Please make sure to replace /home/yathin in the setup files with the actual path of your project directory and in test.py.
```

## Implementation Details
The implementation details of each file are as follows:

- **setup.py**: Python script to configure the build process for the project. 
- **bindings.cpp**: C++ file defining the Python bindings for the plugin interface.
- **plugin_interface.cpp**: C++ file defining the abstract interface for plugins.
- **plugin_loader.cpp**: C++ file implementing the plugin loader functionality.
- **plugin_loader.h**: Header file declaring the plugin loader class.


 
 here are all the files where `/home/yathin` is present replace it with the actual path:


## Setup
### In `bindings.cpp`:

```cpp
#include <torch/extension.h>
#include <pybind11/pybind11.h>
#include "plugin_interface.h"
#include "plugin_loader.h"

// Change the include path to the actual path of your project
#include "/home/yathin/plugin/src/your_project"

// Change the include path to the actual path of libtorch
#include "/home/yathin/plugin/libtorch/include"

// Change the include path to the actual path of pybind11
#include "/home/yathin/plugin/pybind11/include"

// Make sure to replace "/home/yathin/plugin" with the actual path where libtorch is installed
#include "/home/yathin/plugin/libtorch/include/torch/csrc/api/include"
```

```cpp
In plugin_loader.cpp:
cpp
Copy code
// Make sure to replace "/home/yathin" with the actual path where your plugin library is located
plugin_path = "/home/yathin/plugin/libmyplugin.so"
In plugin1.cpp:
cpp
Copy code
// Change the include path to the actual path of your project
#include "../plugin_interface.h"
In plugin_loader.h:
cpp
Copy code
// Make sure to replace "/home/yathin" with the actual path where your plugin library is located
#include "/home/yathin/plugin/libmyplugin.so"
```


## In setup.py:
python
Copy code
```cpp
# Make sure to replace "/home/yathin" with the actual path of your project directory
-I/home/yathin/plugin/src/your_project

# Make sure to replace "/home/yathin" with the actual path where libtorch is installed
-I/home/yathin/plugin/libtorch/include

# Make sure to replace "/home/yathin" with the actual path where pybind11 is installed
-I/home/yathin/plugin/pybind11/include

# Make sure to replace "/home/yathin" with the actual path where your plugin library is located
-I/home/yathin/plugin/libtorch/include/torch/csrc/api/include
```


Before building the project, make sure to set the `LD_LIBRARY_PATH` environment variable to include the location of the libtorch library. You can do this by running the following command:

```bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/yathin/plugin/libtorch/lib
```
## Building the Project

To build the project, run the following command:

```bash
python setup.py build --plugin={name of the plugin}
```

After building, the mylibrary.so file will be created.

## Running the Test
The path to the mylibrary.so file will be declared in the test.py script. You can run the test script using the following command:

```bash
python test.py
```
Make sure to replace the path to the .so file with the actual path in the directory.

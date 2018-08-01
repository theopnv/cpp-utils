![license](https://img.shields.io/github/license/mashape/apistatus.svg)
![](https://img.shields.io/badge/Language-Cpp17-lightgrey.svg)

# cpp-utils
C++ Utilities to use for everyday projects.
Fully tested on **Linux** and **Windows** x64 with C++17. Some libraries if not all, should work on MacOS.

The libraries, classes and methods are well documented in the code.

**Disclaimer:** subject to major and breaking changes while I'm still working in it, this is a WIP.

#### Compilation & Linking
Each part can be compiled as a static library (or header-only for some) with its own CMakeFile.

The **easiest way** to have all the libraries included in your project is to :
1. Add this repository as a git submodule of your project (`$ git submodule add https://github.com/theo-pnv/cpp-utils.git`)
2. Add this line at the top of your root CMakeFile : `add_subdirectory(cpp-utils)`


| Name     | Linking  | Description | Todo |
|----------|----------|-------------|---------|
| **tp_network** | _header-only_ | Asynchronous server and client written in with boost Asio (https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio.html). Can exchange data serialized as string. Asio is included as a header-only standalone so we don't need to have it installed on the system or included. | 1. Support of UDP |
| **tp_serializer** | _static_ | Serialization/Deserialization library. Works very well with tp_network, as it allows to send and receive various custom objects. Based on jsoncpp (https://github.com/open-source-parsers/jsoncpp). Jsoncpp is included as a header-only standalone so we don't need to have it installed on the system or included. | |
| **neon_engine** | _static_ | A small game engine written on top of the SDL2 library (included as a standalone in the project). Supports text and pictures thanks to SDL2_ttf & SDL2_image. (Not functional on linux for now). | 1. UI objects integrated to the ECS 2. Linux compatibility |
| **tp_dlloader** | _static_ | Dynamic Library Loader. It retrieves a class from a shared library file. More info on the processus can be found here : https://theopnv.com/dynamic-loading/ | |
| **tp_filesystem** | _static_ | Abstractions to access files and folders, and to read, write in them. | |
| **tp_rloader** | _static_ | Resources Loader. It allows the creation of a resource folder, like AppData for Windows applications. Retrieving resources from the code is then easier. | |
| **tp_singleton** | _header-only_ | Abstraction of the singleton pattern. | |
| **tp_windows_utility** | _static_ | Small winAPI utilities | |

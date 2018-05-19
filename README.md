![license](https://img.shields.io/github/license/mashape/apistatus.svg)
![](https://img.shields.io/badge/Language-Cpp17-lightgrey.svg)

# cpp-utils
C++ Utilities to use for everyday projects.
Fully tested on **Linux** and **Windows** x64 with C++17. Some libraries if not all, should work on MacOS.

Each part can be compiled as a static library (or header-only for some) with its cmake.

| Name     | Linking  | Description |
|----------|----------|-------------|
| **tp_network** | _header-only_ | Asynchronous server and client written in with boost Asio (https://www.boost.org/doc/libs/1_65_1/doc/html/boost_asio.html). Can exchange data serialized as string. Asio is included as a header-only standalone so we don't need to have it installed on the system or included. _Note: Only supports TCP communication for now._ |
| **tp_serializer** | _static_ | Serialization/Deserialization library. Works very well with tp_network, as it allows to send and receive various custom objects. Based on jsoncpp (https://github.com/open-source-parsers/jsoncpp). Jsoncpp is included as a header-only standalone so we don't need to have it installed on the system or included. |
| **Dlloader** | _static_ | Dynamic Library Loader. It retrieves a class from a shared library file. More info on the processus can be found here : https://theopnv.com/dynamic-loading/ |
| **Filesystem** | _static_ | Abstractions to access files and folders, and to read, write in them. |
| **RLoader** | _static_ | Resources Loader. It allows the creation of a resource folder, like AppData for Windows applications. Retrieving resources from the code is then easier. |
| **Singleton** | _header-only_ | Abstraction of the singleton pattern. |
| **WindowsUtility** | _static_ | Small winAPI utilities |

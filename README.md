![license](https://img.shields.io/github/license/mashape/apistatus.svg)
![](https://img.shields.io/badge/Language-Cpp17-lightgrey.svg)

# cpp-utils
C++ Utilities to use for everyday projects.
Fully tested on Linux and Windows x64 with C++17. Some libraries if not all, should work on OSX.

Each part can be compiled as a static library with its cmake.

**DLLoader** stands for Dynamic Library Loader. It retrieves a class from a shared library file. More info on the processus can be found here : https://theopnv.com/dynamic-loading/

**FileSystem** gathers all abstractions to access files and folders, and to read, write in them.

**RLoader** stands for Resources Loader. It allows the creation of a resource folder, like AppData for Windows applications. Retrieving resources from the code is then easier.

**Singleton** is a single header. As its name implies, it is an asbtraction of the singleton pattern.

**WindowsUtility** is a gathering of small windows API utilities.

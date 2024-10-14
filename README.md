_TODO: simple project description_

> [!NOTE]
> TODO: add commit related source files

**Table of contents :**
- [1. Requirements](#1-requirements)
  - [1.1. C++ Standards](#11-c-standards)
  - [1.2. Dependencies](#12-dependencies)
- [2. How to build](#2-how-to-build)
- [3. How to use](#3-how-to-use)
- [4. Library details](#4-library-details)
- [6. License](#6-license)

# 1. Requirements
## 1.1. C++ Standards

This library requires at least **C++ 11** standard

## 1.2. Dependencies

Below, list of required dependencies:

| Dependencies | VCPKG package | Comments |
|:-:|:-:|:-:|
| [Qt][qt-official] | / | Library built with **Qt framework** |
| [Google Tests][gtest-repo] | `gtest` | Only needed to run unit-tests |

> Dependency manager [VCPKG][vcpkg-tutorial] is not mandatory, this is only a note to be able to list needed packages

# 2. How to build

This library can be use as an _embedded library_ in a subdirectory of your project (like a _git submodule_ for example) :
1. In the **root** CMakeLists, add instructions :
```cmake
add_subdirectory(MyLibrary) # Or if library is put in a folder "dependencies" : add_subdirectory(dependencies/MyLibrary)
```

1. In the **application/library** CMakeLists, add instructions :
```cmake
# Link needed libraries
target_link_libraries(${PROJECT_NAME} PRIVATE mylibrary)
```

# 3. How to use

_TODO: Describe how to use library_

# 4. Library details

_TODO: Sections that can be described are: implementation/tips and tricks/alternatives_

# 6. License

This library is licensed under [MIT license][repo-license].
_TODO: give more details about original project, this is a FORK project_

<!-- Links of this repository -->
[repo-license]: LICENSE

<!-- External links -->
[doxygen-official]: https://www.doxygen.nl/index.html
[example-doc-web]: https://www.google.com/
[gtest-repo]: https://github.com/google/googletest

[qt-official]: https://www.qt.io/
[qt-installer]: https://www.qt.io/download-qt-installer

[vcpkg-tutorial]: https://github.com/legerch/develop-memo/tree/master/Toolchains/Build%20systems/VCPKG
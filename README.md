Library fork used to provide an _advanced Qt Media Player_ based on [FFmpeg][ffmpeg-home] library.

> [!NOTE]
> I'm not the original author of this library, this repository is only a fork from [QtAvPlayer][qtavplayer-repo]

**Table of contents :**
- [1. Fork details](#1-fork-details)
  - [1.1. Purposes](#11-purposes)
  - [1.2. Original files sources](#12-original-files-sources)
  - [1.3. Compatibility](#13-compatibility)
- [2. Requirements](#2-requirements)
  - [2.1. C++ Standards](#21-c-standards)
  - [2.2. Dependencies](#22-dependencies)
- [3. How to build](#3-how-to-build)
  - [3.1. CMake usage](#31-cmake-usage)
  - [3.2. CMake options](#32-cmake-options)
- [4. How to use](#4-how-to-use)
  - [4.1. Logging category](#41-logging-category)
- [5. FFmpeg library usage](#5-ffmpeg-library-usage)
- [6. License](#6-license)

# 1. Fork details
## 1.1. Purposes

Original library was hard to build due to:
- Usage of _Qt private headers_ (which heavily depends on how Qt was installed and the version used)
- Some _CMake hacks_ (source directory had to be set manually, some directories where includes and exported when building target)

So this fork aim to mainly fix those issues (and try some "workaround" to later propose a pull request to the original repository)

> [!TIP]
> See [changelog][repo-changelog] for more details

## 1.2. Original files sources

Below, current associated source files of this fork repository:

| QtAvPlayer | Qt internal files |
|:-:|:-:|
| [746db8051b0c0d687bc2148308f7761e91ec3f98](https://github.com/valbok/QtAVPlayer/commit/746db8051b0c0d687bc2148308f7761e91ec3f98) | [Qt 6.8.0](https://github.com/qt/qtmultimedia/tree/6.7.2/src/multimedia/video) |

## 1.3. Compatibility

Those symbols will be used:
- :dizzy:: Untested (either lack of time, either because unable to access the device to perform tests)
- :x:: Not working
- :last_quarter_moon:: Partial support
- :white_check_mark:: Tested and working

| / | Qt `5.12 -> 5.15.2` | Qt `6.0 -> 6.8` | HW accelerated feature | Comments |
|:-:|:-:|:-:|:-:|:-:|
| Linux (Ubuntu) | :white_check_mark: | :white_check_mark: | :last_quarter_moon: | HW support:<br>- **Wayland** supported (require packages: `libva-dev`)<br>- **X11** unsupported |
| Windows | :white_check_mark: | :white_check_mark: | :white_check_mark: | / |
| MacOS | :dizzy: | :dizzy: | :dizzy: | / |
| iOS | :dizzy: | :dizzy: | :dizzy: | / |
| Android | :dizzy: | :dizzy: | :dizzy: | / |
 
# 2. Requirements
## 2.1. C++ Standards

This library requires at least **C++ 11** standard

## 2.2. Dependencies

Below, list of required dependencies:

| Dependencies | VCPKG package | Comments |
|:-:|:-:|:-:|
| [Qt][qt-official] | / | Library built with **Qt framework** |
| [FFmpeg][ffmpeg-home] | `ffmpeg` | / |

> Dependency manager [VCPKG][vcpkg-tutorial] is not mandatory, this is only a note to be able to list needed packages

# 3. How to build
## 3.1. CMake usage
This library can be use as an _embedded library_ in a subdirectory of your project (like a _git submodule_ for example) :
1. In the **root** CMakeLists, add instructions :
```cmake
add_subdirectory(qtavplayer) # Or if library is put in a folder "dependencies" : add_subdirectory(dependencies/qtavplayer)
```

2. In the **application/library** CMakeLists, add instructions :
```cmake
# Link needed libraries
target_link_libraries(${PROJECT_NAME} PRIVATE qtavplayer)
```

## 3.2. CMake options

This library provide some **CMake** options:
- `QTAVPLAYER_MULTIMEDIA`: Use to enable/disable _QtMultimedia_ support. **Default value:** `ON`.
- Enable/disable hardware accelerated support for each supported OS without having to check current platform build (if disabled, software decoding will be used):
  - `QTAVPLAYER_HW_SUPPORT_WINDOWS`: Support for **Windows** using _D3D11_ API. **Default value:** `ON`.
  - `QTAVPLAYER_HW_SUPPORT_MACOS`: Support for **MacOs** using _Metal_ API. **Default value:** `ON`.
  - `QTAVPLAYER_HW_SUPPORT_LINUX_WAYLAND`: Support for **Linux Wayland** systems using _libva-drm_ API. **Default value:** `ON`.
  - `QTAVPLAYER_HW_SUPPORT_ANDROID`: Support for **Android** using _MediaCodec_ API. **Default value:** `ON`.
  - `QTAVPLAYER_HW_SUPPORT_IOS`: Support for **iOS** using _Metal_ API. **Default value:** `ON`.

# 4. How to use
## 4.1. Logging category

Some classes have more fine-grained logging category:
- **Player backend** (which is _FFmpeg_): `qtavplayer.backend`
- **QAVPlayer:** `qtavplayer.player`
- **QAVVideoCodec:** `"qtavplayer.videocodec"`

Then we can enable/disable logs for those by using [QLoggingCategory][qt-doc-qlogging] appropriate method:
```cpp
// Manage Qt logging category
QLoggingCategory::setFilterRules(QStringLiteral(
    "qtavplayer.backend.*=true\n"           // Enable all logging level for "backend" category
    "qtavplayer.player.debug=false\n"       // Disable debug logging, all others are enabled
    "qtavplayer.videocodec.debug=false\n"
    "qtavplayer.videocodec.info=true"
));
```

# 5. FFmpeg library usage

FFmpeg documentation is available on [their website][ffmpeg-home] ([and API documentation][ffmpeg-doc-api]).  
FFmpeg allow to set multiple options through their dictionary:
- `fflags`: match flags defined under `AVFMT_FLAG_*` values, available at [avformat header API doc][ffmpeg-doc-api-fflags]
- `flags`: match flags defined under `AV_CODEC_FLAG_*` values, available at [avcodec header API doc][ffmpeg-doc-api-flags]
- Context options: multiple context structure fields can be set through the dictionary, like `max_delay`, `probesize`, etc.... Available fields can be seen at [AVFormatContext API doc][ffmpeg-doc-api-context]

# 6. License

[QtAvPlayer][qtavplayer-repo] library is released under [MIT License][repo-license], so this library too.

<!-- Links of this repository -->
[repo-changelog]: CHANGELOG.md
[repo-license]: LICENSE.md

<!-- External links -->
[doxygen-official]: https://www.doxygen.nl/index.html
[ffmpeg-home]: https://www.ffmpeg.org/
[ffmpeg-doc-api]: https://ffmpeg.org/doxygen/trunk/index.html
[ffmpeg-doc-api-context]: https://ffmpeg.org/doxygen/trunk/structAVFormatContext.html
[ffmpeg-doc-api-flags]: https://www.ffmpeg.org/doxygen/trunk/group__lavc__core.html
[ffmpeg-doc-api-fflags]: https://www.ffmpeg.org/doxygen/trunk/avformat_8h.html
[gtest-repo]: https://github.com/google/googletest
[qtavplayer-repo]: https://github.com/valbok/QtAVPlayer
[qt-doc-qlogging]: https://doc.qt.io/qt-6/qloggingcategory.html

[qt-official]: https://www.qt.io/
[qt-installer]: https://www.qt.io/download-qt-installer

[vcpkg-tutorial]: https://github.com/legerch/develop-memo/tree/master/Toolchains/Build%20systems/VCPKG
cmake_minimum_required(VERSION 3.19)

# Set project properties
set(PROJECT_NAME qtavplayer)
set(PROJECT_VERSION_SEMANTIC 0.0.1)
set(PROJECT_VERSION_CPP_MIN 11)

# Set project configuration
## Generic properties
project(${PROJECT_NAME} LANGUAGES CXX)
project(${PROJECT_NAME} VERSION "${PROJECT_VERSION_SEMANTIC}")

## Qt specific properties
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Define project options
## Example: option(LIBRARYNAME_BUILD_TESTS "Use to enable/disable build of unit-tests." ON)
option(QTAVPLAYER_MULTIMEDIA "Use to enable/disable QtMultimedia support" ON)

option(QTAVPLAYER_HW_SUPPORT_WINDOWS        "Use to enable/disable hardware accelerated support for Windows" ON)
option(QTAVPLAYER_HW_SUPPORT_MACOS          "Use to enable/disable hardware accelerated support for MacOS" ON)
option(QTAVPLAYER_HW_SUPPORT_LINUX_WAYLAND  "Use to enable/disable hardware accelerated support for Linux Wayland" ON)
option(QTAVPLAYER_HW_SUPPORT_ANDROID        "Use to enable/disable hardware accelerated support for Android" ON)
option(QTAVPLAYER_HW_SUPPORT_IOS            "Use to enable/disable hardware accelerated support for iOS" ON)

# Set C++ standard to use
if(DEFINED CMAKE_CXX_STANDARD)
    if(${CMAKE_CXX_STANDARD} LESS ${PROJECT_VERSION_CPP_MIN})
        message(FATAL_ERROR "Project ${PROJECT_NAME} require at least C++ standard ${PROJECT_VERSION_CPP_MIN}")
    endif()
else()
    set(CMAKE_CXX_STANDARD ${PROJECT_VERSION_CPP_MIN})
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "Project \"${PROJECT_NAME}\" compiled with C++ standard ${CMAKE_CXX_STANDARD}")

# Set needed packages
## FFmpeg (since Qt also embed his own version of FFmpeg, package must be searched BEFORE Qt)
find_package(FFMPEG 7.0.0 REQUIRED)
message(DEBUG "Result after finding FFmpeg package: ${FFMPEG_LIBRARIES} (${FFMPEG_LIBRARY_DIRS})")

## Qt packages
### Search packages
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Multimedia REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Multimedia REQUIRED)

### Find private packages
if(${QT_VERSION_MAJOR} EQUAL 6)
    message(STATUS "Project \"${PROJECT_NAME}\" compiled with Qt6 toolchain")
    set(QT_DIR_PRIV_SOURCES ${Qt6Multimedia_PRIVATE_INCLUDE_DIRS})

elseif(${QT_VERSION_MAJOR} EQUAL 5)
    message(STATUS "Project \"${PROJECT_NAME}\" compiled with Qt5 toolchain")
    set(QT_DIR_PRIV_SOURCES ${Qt5Multimedia_PRIVATE_INCLUDE_DIRS})

else()
    message(FATAL_ERROR "Project ${PROJECT_NAME} only support Qt5 or Qt6 toolchains, found Qt${QT_VERSION_MAJOR} toolchain")
endif()

## Other library packages
### Example: find_package(nlohmann_json 3.11.3 REQUIRED)

# Defines useful path variables for easier CMake configuration
set(PROJECT_DIR_PUBLIC_HEADERS_ROOT "${PROJECT_SOURCE_DIR}/include")
set(PROJECT_DIR_PUBLIC_HEADERS      "${PROJECT_DIR_PUBLIC_HEADERS_ROOT}/${PROJECT_NAME}")
set(PROJECT_DIR_PRIV_SOURCES        "${PROJECT_SOURCE_DIR}/src")
set(PROJECT_FILE_GLOBAL             "${PROJECT_DIR_PUBLIC_HEADERS}/qtavplayer_global.h")

# Manage library files
## Configure file project - File containing macros that can be used in project
configure_file("${PROJECT_FILE_GLOBAL}.in" "${PROJECT_FILE_GLOBAL}")

## Set library compilation definitions
set(PROJECT_DEF_PRIV
    "QTAVPLAYER_LIBRARY_BUILD"
)

## Set library linking
### Linking dirs
set(PROJECT_LINKING_DIR
    ${FFMPEG_LIBRARY_DIRS}
)

### Linking libs
set(PROJECT_LINKING_LIB
    ### Qt related
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::GuiPrivate
    Qt${QT_VERSION_MAJOR}::Multimedia

    ### FFMPEG related
    ${FFMPEG_LIBRARIES}
)

## Set library files
### Public interface
set(PROJECT_HEADERS_PUBLIC
    qavaudioconverter.h
    qavaudioformat.h
    qavaudioframe.h
    qavaudiooutput.h
    qavaudiooutputdevice.h
    qavframe.h
    qaviodevice.h
    qavplayer.h
    qavstream.h
    qavstreamframe.h
    qavsubtitleframe.h
    qavvideoframe.h
)

### Private
set(PROJECT_HEADERS_PRIVATE
    qavaudiocodec_p.h
    qavaudiofilter_p.h
    qavaudioinputfilter_p.h
    qavaudiooutputfilter_p.h
    qavcodec_p.h
    qavcodec_p_p.h
    qavdemuxer_p.h
    qavfilter_p.h
    qavfilter_p_p.h
    qavfiltergraph_p.h
    qavfilters_p.h
    qavframe_p.h
    qavframecodec_p.h
    qavhwdevice_p.h
    qavinoutfilter_p.h
    qavinoutfilter_p_p.h
    qavpacket_p.h
    qavpacketqueue_p.h
    qavstreamframe_p.h
    qavsubtitlecodec_p.h
    qavvideobuffer_cpu_p.h
    qavvideobuffer_gpu_p.h
    qavvideobuffer_p.h
    qavvideocodec_p.h
    qavvideofilter_p.h
    qavvideoinputfilter_p.h
    qavvideooutputfilter_p.h
)

set(PROJECT_SOURCES
    qavaudiocodec.cpp
    qavaudioconverter.cpp
    qavaudiofilter.cpp
    qavaudioframe.cpp
    qavaudioinputfilter.cpp
    qavaudiooutput.cpp
    qavaudiooutputdevice.cpp
    qavaudiooutputfilter.cpp
    qavcodec.cpp
    qavdemuxer.cpp
    qavfilter.cpp
    qavfiltergraph.cpp
    qavfilters.cpp
    qavframe.cpp
    qavframecodec.cpp
    qavinoutfilter.cpp
    qaviodevice.cpp
    qavpacket.cpp
    qavplayer.cpp
    qavstream.cpp
    qavstreamframe.cpp
    qavsubtitlecodec.cpp
    qavsubtitleframe.cpp
    qavvideobuffer_cpu.cpp
    qavvideobuffer_gpu.cpp
    qavvideocodec.cpp
    qavvideofilter.cpp
    qavvideoframe.cpp
    qavvideoinputfilter.cpp
    qavvideooutputfilter.cpp
)

# Manage platform differences
## Refer to: https://cmake.org/cmake/help/latest/variable/CMAKE_SYSTEM_NAME.html
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PROJECT_DEF_PRIV ${PROJECT_DEF_PRIV}
        "NOMINMAX"  # Needed because Windows define macros "min/max", better to not defined those and use "std::min/std::max" instead
    )

    if(QTAVPLAYER_HW_SUPPORT_WINDOWS)
        message(STATUS "Project \"${PROJECT_NAME}\" have enabled accelerated hardware support for \"Windows\" systems")

        set(PROJECT_HEADERS_PRIVATE ${PROJECT_HEADERS_PRIVATE}
            qavhwdevice_d3d11_p.h
        )

        set(PROJECT_SOURCES ${PROJECT_SOURCES}
            qavhwdevice_d3d11.cpp
        )

        set(PROJECT_DEF_PRIV ${PROJECT_DEF_PRIV}
            "QT_AVPLAYER_D3D11"
        )
    endif()
endif()

if((CMAKE_SYSTEM_NAME STREQUAL "Darwin" AND QTAVPLAYER_HW_SUPPORT_MACOS) OR (CMAKE_SYSTEM_NAME STREQUAL "iOS" AND QTAVPLAYER_HW_SUPPORT_IOS))
    message(STATUS "Project \"${PROJECT_NAME}\" have enabled accelerated hardware support for \"Apple\" systems")

    set(PROJECT_SOURCES ${PROJECT_SOURCES}
        qavhwdevice_videotoolbox.mm
    )

    set(PROJECT_DEF_PRIV ${PROJECT_DEF_PRIV}
        "QT_AVPLAYER_VTOOLBOX"
    )

    find_library(COREVIDEO_FRAMEWORK CoreVideo)
    find_library(IOSURFACE_FRAMEWORK IOSurface)
    find_library(METAL_FRAMEWORK Metal)
    set(PROJECT_LINKING_LIB ${PROJECT_LINKING_LIB}
        ${COREVIDEO_FRAMEWORK}
        ${IOSURFACE_FRAMEWORK}
        ${METAL_FRAMEWORK}
    )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND QTAVPLAYER_HW_SUPPORT_LINUX_WAYLAND)
    message(STATUS "Project \"${PROJECT_NAME}\" have enabled accelerated hardware support for \"Linux Wayland\" systems")

    set(PROJECT_HEADERS_PRIVATE ${PROJECT_HEADERS_PRIVATE}
        qavhwdevice_vaapi_drm_egl_p.h
    )

    set(PROJECT_SOURCES ${PROJECT_SOURCES}
        qavhwdevice_vaapi_drm_egl.cpp
    )

    set(PROJECT_DEF_PRIV ${PROJECT_DEF_PRIV}
        "QT_AVPLAYER_VA_DRM"
    )

    set(PROJECT_LINKING_LIB ${PROJECT_LINKING_LIB}
        EGL
        va      #libva
        va-drm
    )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Android" AND QTAVPLAYER_HW_SUPPORT_ANDROID)
    message(STATUS "Project \"${PROJECT_NAME}\" have enabled accelerated hardware support for \"Android\" systems")

    set(PROJECT_SOURCES ${PROJECT_SOURCES}
        qavhwdevice_mediacodec.cpp
        qavandroidsurfacetexture.cpp
    )

    set(PROJECT_DEF_PRIV ${PROJECT_DEF_PRIV}
        "QT_AVPLAYER_MEDIACODEC"
    )
endif()

### Prepend all files to proper directory
list(TRANSFORM PROJECT_HEADERS_PUBLIC PREPEND "${PROJECT_DIR_PUBLIC_HEADERS}/")
list(TRANSFORM PROJECT_HEADERS_PRIVATE PREPEND "${PROJECT_DIR_PRIV_SOURCES}/")
list(TRANSFORM PROJECT_SOURCES PREPEND "${PROJECT_DIR_PRIV_SOURCES}/")

set(PROJECT_FILES ${PROJECT_FILE_GLOBAL} ${PROJECT_HEADERS_PUBLIC} ${PROJECT_HEADERS_PRIVATE} ${PROJECT_SOURCES})

# Add files to the library
add_library(${PROJECT_NAME} SHARED ${PROJECT_FILES})

# Set version of library
set_target_properties(${PROJECT_NAME} PROPERTIES
                        VERSION ${PROJECT_VERSION}
                        SOVERSION ${PROJECT_VERSION_MAJOR})

# Link needed libraries
target_link_directories(${PROJECT_NAME} PRIVATE ${PROJECT_LINKING_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_LINKING_LIB})

# Specify compiler options
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -Werror=return-type -Wshadow -Wlogical-op -Wduplicated-cond -Wduplicated-branches>
    $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -Werror=return-type -Wshadow -Wlogical-op -Wduplicated-cond -Wduplicated-branches>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /wd4251>
)

# Compile needed definitions
## Library related
target_compile_definitions(${PROJECT_NAME} PRIVATE ${PROJECT_DEF_PRIV})

## Do we need Qt Multimedia support
if(QTAVPLAYER_MULTIMEDIA)
    target_compile_definitions(${PROJECT_NAME} PUBLIC QT_AVPLAYER_MULTIMEDIA)
endif()

# Specify include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${PROJECT_DIR_PUBLIC_HEADERS_ROOT}  # Only expose public headers
    PRIVATE
        ${PROJECT_DIR_PRIV_SOURCES}         # Internal headers, only for internal use
        ${FFMPEG_INCLUDE_DIRS}              # Needed for FFMPEG library
        ${QT_DIR_PRIV_SOURCES}              # Private Qt headers
)

# Add linker specific flags due to FFMPEG.
# For more details, please refer to:
# https://github.com/microsoft/vcpkg/issues/31185
if(NOT APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-Bsymbolic")
endif()


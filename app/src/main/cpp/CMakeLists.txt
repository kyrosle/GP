# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

cmake_minimum_required(VERSION 3.22.1)
project("gp")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

set(GAME_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(3rdLib)
include_directories(source)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")


# Creates your game shared library. The name must be the same as the
# one used for loading in your Kotlin/Java or AndroidManifest.txt files.
#add_library(gp SHARED
#    main.cpp
#    lib/android_out.cpp
#    lib/Renderer.cpp
#    lib/Shader.cpp
#    lib/TextureAsset.cpp
#    lib/Utility.cpp)

add_subdirectory(3rdLib)
add_subdirectory(source/runtime)

add_library(gp SHARED program.cpp)

# Searches for a package provided by the game activity dependency
find_package(game-activity REQUIRED CONFIG)

# Configure libraries CMake uses to link your target library.
target_link_libraries(gp PUBLIC
    # The game activity
    game-activity::game-activity_static

    GameRuntime

    stb
    imgui
    spdlog
    # EGL and other dependent libraries required for drawing
    # and interacting with Android system
    EGL
    GLESv3
    jnigraphics
    android
    log)

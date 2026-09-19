cmake_minimum_required(VERSION 3.28)
project(blocks2d VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(FetchContent)



# ==========================================
# FETCH SFML
# ==========================================
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/sfml/sfml
    GIT_TAG        3.0.0
    UPDATE_DISCONNECTED ON
)
set(SFML_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(SFML_BUILD_DOC OFF CACHE INTERNAL "")
set(SFML_BUILD_NETWORK OFF CACHE INTERNAL "")
set(SFML_BUILD_AUDIO OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(SFML)



# ==========================================
# FETCH IMGUI & IMGUI-SFML
# ==========================================
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui
    GIT_TAG        v1.91.6-docking
    UPDATE_DISCONNECTED ON
)
FetchContent_MakeAvailable(imgui) 

FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml
    GIT_TAG        v3.0
    UPDATE_DISCONNECTED ON
)

set(IMGUI_DIR "${imgui_SOURCE_DIR}" CACHE PATH "Path to ImGui" FORCE)
set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(imgui-sfml)



# ==========================================
# FIND SYSTEM OPENGL
# ==========================================
find_package(OpenGL REQUIRED)



# ==========================================
# COLLECT PROJECT SOURCE FILES
# ==========================================
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(Blocks2d ${PROJECT_SOURCES})

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/CMakeConfig.hpp.in"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/CMakeConfig.hpp"
)

target_include_directories(Blocks2d PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    "${imgui_SOURCE_DIR}"
    "${imgui-sfml_SOURCE_DIR}"
)



# ==========================================
# LINK LIBRARIES
# ==========================================
target_link_libraries(Blocks2d PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    ImGui-SFML::ImGui-SFML
    OpenGL::GL
)



# ==========================================
# COPY RESOURCES TO BUILD DIRECTORY
# ==========================================
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/res")
    add_custom_command(TARGET Blocks2d POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:Blocks2d>/res"
        COMMENT "Copying resources to build directory..."
    )
endif()

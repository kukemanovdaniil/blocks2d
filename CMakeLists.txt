cmake_minimum_required(VERSION 3.28)
project(Blocks2d VERSION 1.0 LANGUAGES CXX)

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
    GIT_TAG        3.1.0
)

set(SFML_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(SFML_BUILD_DOC OFF CACHE INTERNAL "")
set(SFML_BUILD_NETWORK OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(SFML)

# ==========================================
# FETCH RmlUi
# ==========================================

FetchContent_Declare(
    RmlUi
    GIT_REPOSITORY https://github.com/mikke89/RmlUi
    GIT_TAG        master
)

set(RMLUI_BUILD_SAMPLES OFF CACHE INTERNAL "")
set(RMLUI_ENABLE_SFML_BACKEND OFF CACHE INTERNAL "")
set(RMLUI_ENABLE_GL3_RENDERER OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(RmlUi)
FetchContent_GetProperties(RmlUi SOURCE_DIR RMLUI_SOURCE_DIR)

# ==========================================
# FIND SYSTEM OPENG
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

set(RMLUI_BACKEND_SOURCES
    "${RMLUI_SOURCE_DIR}/Backends/RmlUi_Backend_SFML_GL3.cpp"
    "${RMLUI_SOURCE_DIR}/Backends/RmlUi_Renderer_GL3.cpp"
)

add_executable(Blocks2d ${PROJECT_SOURCES})

target_include_directories(Blocks2d PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

# ==========================================
# LINK LIBRARIES
# ==========================================

target_link_libraries(Blocks2d PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    rmlui
    OpenGL::GL
)

target_compile_definitions(Blocks2d PRIVATE 
    RMLUI_RENDERER_GL3
    RMLUI_PLATFORM_SFML
)

# ==========================================
# COPY RESOURCES TO BUILD DIRECTORY
# ==========================================

add_custom_command(TARGET Blocks2d POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/res"
    "$<TARGET_FILE_DIR:Blocks2d>/res"
    COMMENT "Copying resources to build directory..."
)

cmake_minimum_required(VERSION 3.16)
project(MyRaylibGame LANGUAGES CXX)

# ---- C++ Standard ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ---- Export compile_commands.json (for VS Code / clangd) ----
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Collect Sources ----
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_SOURCE_DIR}/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
)

# ---- Executable ----
add_executable(${PROJECT_NAME} ${SOURCES})

# ---- Include Directories ----
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)

# ---- Find raylib (Homebrew / pkg-config fallback) ----
find_package(raylib QUIET)

if (raylib_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED raylib)

    target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_INCLUDE_DIRS})
    target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARY_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${RAYLIB_LIBRARIES})
endif()

# ---- macOS specific frameworks (usually auto-handled, but safe fallback) ----
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        "-framework CoreVideo"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework GLUT"
        "-framework OpenGL"
    )
endif()
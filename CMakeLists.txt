cmake_minimum_required(VERSION 3.15)
project(FunctionDrawing LANGUAGES CXX C)

# C++ Standard festlegen
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Download SDL
include(FetchContent)
FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
)
set(SDL_TEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(SDL3)

# Download GLM
FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE) # GLM-Tests deaktivieren
FetchContent_MakeAvailable(glm)

# Add GLAD
add_library(GLAD external/glad/src/glad.c)
target_include_directories(GLAD PUBLIC external/glad/include)

# Setup project
add_executable(${PROJECT_NAME} src/main.cpp
        src/shader.cpp
        src/index_buffer.h
        src/shader.h
        src/vertex_buffer.h
        src/defines.h
        src/computingFunc.h
)

# Link libraries
# + Edge case for linux
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 GLAD glm::glm)
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE dl)
endif()

# Add header directories
target_include_directories(${PROJECT_NAME} PRIVATE include external/glad/include)
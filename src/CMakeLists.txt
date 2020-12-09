cmake_minimum_required(VERSION 3.10)

project(RayTracing VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(Config.h.in Config.h)

# Source files
add_executable(RayTracing main.cpp)

set(SRC
    Scene.cpp
    RayTracing.cpp
    Object.cpp
    
    Scene.hpp
    RayTracing.hpp
    Ray.hpp
    Object.hpp
    utils.hpp
)

target_sources(RayTracing PRIVATE "${SRC}")

# GLM
find_package(GLM CONFIG REQUIRED)
target_include_directories(RayTracing PUBLIC "${GLM_INCLUDE_DIRS}")

# OpenCV
find_package(OpenCV CONFIG REQUIRED)
target_include_directories(RayTracing PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(RayTracing ${OpenCV_LIBS})


# Adding include path by default to temporarily fix glm bug
target_include_directories(RayTracing PUBLIC "/usr/local/include")

# target_include_directories(RayTracing PUBLIC "${PROJECT_BINARY_DIR}")

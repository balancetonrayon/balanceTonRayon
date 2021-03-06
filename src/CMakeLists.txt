cmake_minimum_required(VERSION 3.10)

project(RayTracing VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(Config.h.in Config.h)

# Source files
add_executable(RayTracing main.cpp)

set(SRC
    Scene.cpp
    RayTracer.cpp
    Object.cpp
    lodepng.cpp
    Texture.cpp
    
    Scene.hpp
    RayTracer.hpp
    Ray.hpp
    Object.hpp
    ObjParser.hpp
    Texture.hpp
    lodepng.h
#    ImgHandler.hpp
    
    utils.hpp
)

target_sources(RayTracing PRIVATE "${SRC}")

# GLM
find_package(glm CONFIG REQUIRED)
target_include_directories(RayTracing PUBLIC "${GLM_INCLUDE_DIRS}")


# XML Parser
find_package(tinyxml2 CONFIG REQUIRED)
target_include_directories(RayTracing PUBLIC ${tinyxml2_INCLUDE_DIRS})
target_link_libraries(RayTracing ${tinyxml2_LIBS})

# Adding include path by default to temporarily fix glm bug
target_include_directories(RayTracing PUBLIC "/usr/local/include")

# target_include_directories(RayTracing PUBLIC "${PROJECT_BINARY_DIR}")

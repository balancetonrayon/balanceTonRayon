cmake_minimum_required(VERSION 3.12)
# cmake_policy(SET CMP0076 NEW)

project(RayTracing VERSION 1.0)

SET(CUSTOM_COMPILE_FLAGS "-O3 -Wno-comment")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CUSTOM_COMPILE_FLAGS}")

configure_file(Config.h.in Config.h)

# Source files
add_executable(RayTracing main.cpp)

# Sub dirs
add_subdirectory(Object)

set(SRC
    RayTracer.cpp
    Parser.cpp
    lodepng/lodepng.cpp
    Texture.cpp
    
    Scene.hpp
    RayTracer.hpp
    Parser.hpp
    ObjParser.hpp
    lodepng/lodepng.h
    ImgHandler.hpp
    Texture.hpp
    Ray.hpp
)

target_sources(RayTracing PRIVATE "${SRC}")

# GLM
find_package(glm CONFIG REQUIRED)
target_include_directories(RayTracing PUBLIC "${GLM_INCLUDE_DIRS}")


# XML Parser
find_package(tinyxml2 CONFIG REQUIRED)
target_include_directories(RayTracing PUBLIC ${tinyxml2})
target_link_libraries(RayTracing tinyxml2::tinyxml2)

# Adding include path by default to temporarily fix glm bug
target_include_directories(RayTracing PUBLIC "/usr/local/include")

target_include_directories(RayTracing PUBLIC "utils")
target_include_directories(RayTracing PUBLIC .)

# target_include_directories(RayTracing PUBLIC "${PROJECT_BINARY_DIR}")

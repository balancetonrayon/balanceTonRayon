cmake_minimum_required(VERSION 3.12)

set(SRC
    Box.cpp
    Camera.cpp
    DirectLight.cpp
    Light.cpp
    Plane.cpp
    Polygon.cpp
    PolygonMesh.cpp
    Sphere.cpp
    SpotLight.cpp
    Triangle.cpp
    TriangleMesh.cpp

    AeraLight.hpp
    BasicObject.hpp
    Box.hpp
    Camera.hpp
    DirectLight.hpp
    Inter.hpp
    Light.hpp
    PhysicalObject.hpp
    Plane.hpp
    Polygon.hpp
    PolygonMesh.hpp
    Sphere.hpp
    SpotLight.hpp
    Triangle.hpp
    TriangleMesh.hpp
)

list(TRANSFORM SRC PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

target_sources(RayTracing PRIVATE "${SRC}")

#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <vector>
#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "Ray.hpp"
#include "RayTracing.hpp"


struct PhysicalObject
{
    glm::vec3 pos;

    virtual std::ostream &printInfo(std::ostream &os) const = 0;

    explicit PhysicalObject(glm::vec3 pos = glm::vec3()) : pos(pos) {}
    
    friend std::ostream &operator<<(std::ostream &stream, PhysicalObject const &obj)
    {
        return obj.printInfo(stream);
    }
};

struct LightSource : public virtual PhysicalObject
{
    glm::vec3 color;

    std::ostream &printInfo(std::ostream &os) const;

    explicit LightSource(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3()) : PhysicalObject(pos), color(color) {}
};

struct ObjectBase : public virtual PhysicalObject
{
    glm::vec3 color;
    float transparency;
    float refractiveIndex;

    std::vector<Ray> intersect(const Ray ray, const LightSource ltSrc);

    explicit ObjectBase(glm::vec3 pos) : PhysicalObject(pos) {}
    explicit ObjectBase(glm::vec3 pos, float t, float r) : PhysicalObject(pos), transparency(t), refractiveIndex(r) {}
};

struct Camera : public virtual PhysicalObject
{
    // Size of the screen
    float sizeX;
    float sizeY;

    // Resolution of the screen
    unsigned resX;
    unsigned resY;

    float focalLength;

    Ray genRay(unsigned x, unsigned y);
    std::ostream &printInfo(std::ostream &os) const;

    explicit Camera(glm::vec3 pos = glm::vec3(), float sx = 1, float sy = 1, unsigned rx = 1000, unsigned ry = 1000, float fL = 1) : PhysicalObject(pos), sizeX(sx), sizeY(sy),
                                                                                                                                     resX(rx), resY(ry), focalLength(fL) {}
};

struct Plane : public virtual ObjectBase
{
    glm::vec3 normal; //Orthogonal vector in unit length

    std::vector<Ray> intersect(const Ray ray, const LightSource ltSrc);
    std::ostream &printInfo(std::ostream &os) const;

    explicit Plane(glm::vec3 pos = glm::vec3(), glm::vec3 normal = glm::vec3(1, 1, 1)) : ObjectBase(pos), normal(glm::normalize(normal)) {}
};

struct Sphere : public virtual ObjectBase
{
    float radius;

    std::vector<Ray> intersect(const Ray ray, const LightSource ltSrc);

    explicit Sphere(glm::vec3 pos, float radius) : ObjectBase(pos), radius(radius) {}

    std::ostream &printInfo(std::ostream &os) const;
};

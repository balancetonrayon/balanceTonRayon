#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <vector>
#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "Ray.hpp"
#include "RayTracing.hpp"

std::ostream &operator<<(std::ostream &out, const glm::vec3 &vec)
{
    out << "{"
        << vec.x << " " << vec.y << " " << vec.z
        << "}";

    return out;
}

struct PhysicalObject
{
    glm::vec3 pos;

    explicit PhysicalObject(glm::vec3 pos = glm::vec3()) : pos(pos) {}

    virtual std::ostream &printInfo(std::ostream &os) const = 0;
};

struct LightSource : public virtual PhysicalObject
{
    glm::vec3 color;

    explicit LightSource(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3()) : PhysicalObject(pos), color(color) {}

    std::ostream &printInfo(std::ostream &os) const
    {
        return os << "LightSource: in " << pos << ", of color: " << color;
    }
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

    Ray genRay(unsigned x, unsigned y)
    {
        //EXCEPTION A AJOUTER
        glm::vec3 dir((0.5 - ((float)x) / resX) * sizeX, (-0.5 + ((float)y) / resY) * sizeY, focalLength);
        return Ray(pos, glm::normalize(dir));
    };

    explicit Camera(glm::vec3 pos = glm::vec3(), float sx = 1, float sy = 1, unsigned rx = 1000, unsigned ry = 1000, float fL = 1) : PhysicalObject(pos), sizeX(sx), sizeY(sy),
                                                                                                                                     resX(rx), resY(ry), focalLength(fL) {}

    std::ostream &printInfo(std::ostream &os) const
    {
        return os << "Camera: in " << pos << ", of size: " << sizeX;
    }
};

struct Plane : public virtual ObjectBase
{
    glm::vec3 normal; //Orthogonal vector in unit length

    std::vector<Ray> intersect(const Ray ray, const LightSource ltSrc)
    {
        std::vector<Ray> rays;
        // Calcul du point d'intersection
        float distance;
        bool inter = glm::intersectRayPlane(ray.initPt, ray.dir, pos, normal, distance);
        glm::vec3 intersectPt = distance * ray.initPt;
        glm::vec3 dir = glm::normalize(intersectPt - ltSrc.pos);

        // Si la source n'est pas derrière le plan, on ajoute le rayon réfléchi
        if (glm::dot(dir, normal) > 0)
        {
            rays.push_back(Ray(intersectPt, dir));
        }
        return rays;
    }

    explicit Plane(glm::vec3 pos = glm::vec3(), glm::vec3 normal = glm::vec3(1, 1, 1)) : ObjectBase(pos), normal(glm::normalize(normal)) {}

    std::ostream &printInfo(std::ostream &os) const
    {
        return os << "Plane: in " << pos << ", of normal " << normal;
    }
};

struct Sphere : public virtual ObjectBase
{
    float radius;

    std::vector<Ray> intersect(const Ray ray, const LightSource ltSrc)
    {
        std::vector<Ray> rays;

        glm::vec3 intersectPt;
        glm::vec3 normal;
        bool inter = glm::intersectRaySphere(ray.initPt, ray.dir, pos, radius, intersectPt, normal);

        glm::vec3 dir = glm::normalize(intersectPt - ltSrc.pos);

        // Si la source n'est pas derrière la sphère, on ajoute le rayon réfléchi
        if (glm::dot(dir, normal) > 0)
        {
            rays.push_back(Ray(intersectPt, dir));
        }
        return rays;
    }

    explicit Sphere(glm::vec3 pos, float radius) : ObjectBase(pos), radius(radius) {}

    std::ostream &printInfo(std::ostream &os) const
    {
        return os << "Sphere: in " << pos << ", of radius: " << radius;
    }
};

std::ostream &operator<<(std::ostream &stream, PhysicalObject const &obj)
{
    return obj.printInfo(stream);
}
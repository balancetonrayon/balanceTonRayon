#pragma once
#include <vector>
#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include "ray.hpp"

struct PhysicalObject
{
    glm::vec3 pos;

    explicit PhysicalObject(glm::vec3 pos) : pos(pos) {}
};

struct ObjectBase : public PhysicalObject
{
    glm::vec3 color;
    float transparency;
    float refractiveIndex;

    std::vector<Ray> intersect(const Ray ray, const LightSource ltSrc);

    explicit ObjectBase(glm::vec3 pos) : PhysicalObject(pos) {}
};

struct LightSource : public PhysicalObject
{
    glm::vec3 color;
};

struct Camera : public PhysicalObject
{
    unsigned resX;
    unsigned resY; 
    float focalLength;

    Ray genRay(unsigned x, unsigned y) {
        glm::vec3 dir;
        return Ray(pos, dir);
    };
};

struct Plane : public ObjectBase
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

    Plane();

    explicit Plane(glm::vec3 pos, glm::vec3 normal) : ObjectBase(pos), normal(glm::normalize(normal)) {}

    ~Plane();
};

struct Sphere : public ObjectBase
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

    Sphere();

    explicit Sphere(glm::vec3 pos, float radius) : ObjectBase(pos), radius(radius) {}

    ~Sphere();
};

#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <memory>
#include <vector>

#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>

#include "Ray.hpp"
#include "Texture.hpp"
#include "BasicObject.hpp"

//!  The Sphere class.
/**
    \class Sphere
  @brief It represents a solid sphere.
*/
class Sphere : public BasicObject {
public:
    //! A public variable.
    /**
      @brief The radius of the sphere.
    */
    float radius;

    /**
     * @brief Computes the intersection between a Ray and a Sphere.
     *
     * @param iRay the incoming Ray
     * @param ltSrc the light source of the scene
     * @param inter the intersection object which contains the intersection information
     * @sa Inter
     * @param rays The rays created by the intersection
     */
    void intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                   std::vector<Ray> &rays) const override;

    /**
     * @brief Construct a Sphere at (0, 0, 0) of radius 1 by default.
     *
     * @param pos the coordinates of the sphere
     * @param color the color of the sphere
     * @param radius the radius of the sphere
     * @param t the transparency of the sphere
     * @param r the reflexion index of the sphere
     * @param R the refraction index of the sphere
     * @param a the albedo of the sphere
     */
    explicit Sphere(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                    float radius = 1, float t = 0, float r = 0, float R = 0, float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), radius(radius) {}

protected:
    //! @brief A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

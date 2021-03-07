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

/**
 * @brief Class representing a solid plane
 * @class Plane
 *
 */
class Plane : public BasicObject {
public:
    /**
     * @brief The normal vector of the plane.
     *
     */
    glm::vec3 normal;

public:
    void intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                   std::vector<Ray> &rays) const override;

    /**
     * @brief Construct a Plan of normal (0, 0, 1) and containing (0, 0, 0) by default.
     *
     * @param pos the origin of the plan
     * @param color the colour of the plan if no texture is defined
     * @param normal the normal vector of the plan
     * @param t the transparency of the plan if no texture is defined
     * @param r the reflexion index of the plan
     * @param R the refractive index of the plan
     * @param a the albedo of the plan
     */
    explicit Plane(glm::vec3 pos = glm::vec3(), glm::vec3 normal = glm::vec3(0, 0, 1),
                   glm::vec3 color = glm::vec3(1, 1, 1), float t = 0, float r = 1, float R = 1,
                   float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), normal(glm::normalize(normal)) {}

    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

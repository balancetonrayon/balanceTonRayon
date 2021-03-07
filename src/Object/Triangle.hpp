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
  \class Triangle
  @brief It represents a solid triangle.
*/
class Triangle : public BasicObject {
public:
    //! A public variable.
    /**
      @brief The second vertex of the triangle.
    */
    glm::vec3 pos1;

    //! A public variable.
    /**
     @brief  The third vertex of the triangle.
    */
    glm::vec3 pos2;

    //! A public variable.
    /**
      @brief The normal of the triangle.
    */
    glm::vec3 normal;

    /**
     * @brief
     *
     * @param iRay
     * @param ltSrc
     * @param inter
     * @param rays
     */
    void intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                   std::vector<Ray> &rays) const override;

    /**
     * @brief
     *
     * @param position
     */
    void offset(const glm::vec3 &position) {
        pos = pos + position;
        pos1 = pos1 + position;
        pos2 = pos2 + position;
    }

    //! A specialized constructor.

    /**
     * @brief Construct a new Triangle object
     *
     * @param v0 the first vertex
     * @param v1 the second vertex
     * @param v2 the third vertex
     * @param n the normal
     * @param color the color of the triangle
     * @param t the transparency of the triangle
     * @param r the reflexion indexof the triangle
     * @param R the refraction index of the triangle
     * @param a the albedo of the triangle
     */
    explicit Triangle(glm::vec3 v0 = glm::vec3(), glm::vec3 v1 = glm::vec3(),
                      glm::vec3 v2 = glm::vec3(), glm::vec3 n = glm::vec3(1, 1, 1),
                      glm::vec3 color = glm::vec3(1, 1, 1), float t = 0, float r = 0, float R = 0,
                      float a = 0.18)
        : BasicObject(v0, color, t, r, R, a), pos1(v1), pos2(v2), normal(glm::normalize(n)) {
        if (n.x == 1 && n.y == 1 && n.z == 1) normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
    }

protected:
    //! @brief A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

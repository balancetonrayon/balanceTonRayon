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

class Box : public BasicObject {
public:
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 pos3;

    void intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                   std::vector<Ray> &rays) const override;

    /**
     * @brief Construct a new Box object
     *
     * @param v0
     * @param v1
     * @param v2
     * @param v3
     * @param color
     * @param t
     * @param r
     * @param R
     * @param a
     */
    explicit Box(glm::vec3 v0 = glm::vec3(), glm::vec3 v1 = glm::vec3(), glm::vec3 v2 = glm::vec3(),
                 glm::vec3 v3 = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1), float t = 0,
                 float r = 1, float R = 1, float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), pos1(pos1), pos2(pos2), pos3(pos3) {}

protected:
    //! @brief A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

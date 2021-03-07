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
#include "PhysicalObject.hpp"

/**
 * \brief The object represents a light-source, which is located at pos.
 * @class Light
 *
 */
class Light : public PhysicalObject {
public:
    //! A public variable.
    /**
      color represents the color of the light-source. color elements are between
      0 and 1.
    */
    glm::vec3 color;

    //! A public variable.
    /**
      intensity represents the color of the light-source. color elements are
      between 0 and 1.
    */
    float intensity;

    /**
     * @brief A pure virtual function computing the rays going from the intersection point to the
     * light sources.
     *
     * @param hitPt the intersection point
     * @param rays the resulting rays
     */
    virtual void outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const = 0;

    /**
     * @brief Construct a new Light at (0, 0, 0), and selects (0, 0, 0) as the color of the
       source by default.
     *
     * @param pos
     * @param color
     * @param i
     */
    explicit Light(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1), float i = 1)
        : PhysicalObject(pos), color(color), intensity(i) {}

protected:
    /**
      @fn std::ostream &printInfo(std::ostream &os) const override
      @brief A normal member taking one argument and returning the information about
         an object.
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

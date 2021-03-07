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
#include "Light.hpp"

//!  The DirectLight class.
/**
  It represents a light which is infinetely far.
*/
class DirectLight : public Light {
public:
    //! A normal member computing the rays going from the intersect
    //! point to the light sources.
    /**
      @param hitPt the intersection point
      @return the resulting rays
    */
    void outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const override;

    /**
     * @brief Construct a new Direct Light at (0, 0, 0), and selects (0, 0, 0) as the color of the
      source by default.
     *
     * @param pos
     * @param color
     * @param i
     */
    explicit DirectLight(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                         float i = 2000)
        : Light(pos, color, i) {}
};

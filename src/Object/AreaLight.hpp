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

//!  The AreaLight class.
/**
  \class AreaLight
  @brief Statistical Area Light
  It represents a light which intensity decreases with the square of the distance
*/
class AreaLight : public Light {
protected:
    /**
     * @brief
     *
     */
    int numberOfRays;
    /**
     * @brief
     *
     */
    glm::vec3 vv;
    /**
     * @brief
     *
     */
    glm::vec3 hv;

public:
    /**
     * @brief
     *
     * @param hitPt
     * @param rays
     */
    void outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const override;

    /**
     * @brief Construct a new Area Light object at (0, 0, 0), and sets the color of the
       source as white by default.
     *
     * @param pos
     * @param color
     * @param i
     * @param n
     */
    explicit AreaLight(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                       float i = 10000, int n = 64)
        : Light(pos, color, i), numberOfRays(n) {}
};

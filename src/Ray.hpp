/**
 * @file Ray.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief
 * @version 0.1
 * @date 2021-03-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <glm/vec3.hpp>

#include "utils.hpp"

/**
 * @brief The object ray is caracterized by an initial point and a direction
 * @class Ray
 */
struct Ray {
protected:
    /**
     * @brief The 3D initial point.
     *
     */
    glm::vec3 initPt;

    /**
     * @brief The direction of the ray.
     *
     */
    glm::vec3 dir;

    /**
     * @brief The color of the ray. Each element of the vec3 is contained in [0, 1].
     *
     */
    glm::vec3 color;

public:
    /**
     * @brief Get the origin of the Ray
     *
     * @return glm::vec3 the coordinates of the origin
     */
    glm::vec3 getInitPt() const { return this->initPt; }

    /**
     * @brief Get the direction of the ray
     *
     * @return glm::vec3 the direction of the ray as a vector
     */
    glm::vec3 getDir() const { return this->dir; }

    /**
     * @brief Get the color of the ray (mainly of the source)
     *
     * @return glm::vec3 the color of the ray as a vector
     */
    glm::vec3 getColor() const { return this->color; }

    /**
     * @brief Set the origin of the Ray
     *
     * @param initPt the coordinates of the origin
     */
    void setInitPt(glm::vec3 initPt) { this->initPt = initPt; }

    /**
     * @brief Set the direction of the ray
     *
     * @param dir the vector of the direction
     */
    void setDir(glm::vec3 dir) { this->dir = dir; }

    /**
     * @brief Set the color of the ray
     *
     * @param color the vector containing the color
     */
    void setColor(glm::vec3 color) { this->color = color; }

    /**
     * @brief Move slightly the origin of the ray in the direction of the normal to avoid acne
     *
     * @param hitNormal the normal of the object
     * @param biaisCoeff the distance of the movement
     */
    void biais(glm::vec3 hitNormal, float biaisCoeff) { initPt = initPt + hitNormal * biaisCoeff; }

    // Constructors
    /** The default constructor
    /**
     * @brief Construct a Ray starting at 0,0,0 and going towards increasing x.
     *
     */
    Ray() : initPt(glm::vec3(0, 0, 0)), dir(glm::vec3(1, 0, 0)) {}

    /** The specialized constructor.
    /**
    * @brief Construct a Ray with specified initial point and direction.
    *
    * @param initPt the origin of the ray
    * @param dir the direction of the ray
    */
    Ray(glm::vec3 initPt, glm::vec3 dir) : initPt(initPt), dir(glm::normalize(dir)) {}

    /**
     * @brief An overload of the operator << to print rays for debug.
     *
     * @param stream the current ostream
     * @param ray the current ray which needs to be printed.
     * @return std::ostream& the information of the object as an ostream.
     */
    friend std::ostream &operator<<(std::ostream &stream, Ray const &ray) {
        return stream << "Ray of initPt: " << ray.initPt << " and direction: " << ray.dir;
    }
};

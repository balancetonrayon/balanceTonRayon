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
     * @brief Get the Init Pt object
     *
     * @return glm::vec3
     */
    glm::vec3 getInitPt() const { return this->initPt; }

    /**
     * @brief Get the Dir object
     *
     * @return glm::vec3
     */
    glm::vec3 getDir() const { return this->dir; }
    /**
     * @brief Get the Color object
     *
     * @return glm::vec3
     */
    glm::vec3 getColor() const { return this->color; }

    /**
     * @brief Set the Init Pt object
     *
     * @param initPt
     * @return glm::vec3
     */
    glm::vec3 setInitPt(glm::vec3 initPt) { this->initPt = initPt; }

    /**
     * @brief Set the Dir object
     *
     * @param dir
     * @return glm::vec3
     */
    glm::vec3 setDir(glm::vec3 dir) { this->dir = dir; }

    /**
     * @brief Set the Color object
     *
     * @param color
     * @return glm::vec3
     */
    glm::vec3 setColor(glm::vec3 color) { this->color = color; }

    /**
     * @brief
     *
     * @param hitNormal
     * @param biaisCoeff
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
    * @param initPt
    * @param dir
    */
    Ray(glm::vec3 initPt, glm::vec3 dir) : initPt(initPt), dir(glm::normalize(dir)) {}

    /**
     //! An overload of the operator << to print rays for debug.
     * @brief
     *
     * @param stream the current ostream
     * @param ray the current ray which needs to be printed.
     * @return std::ostream& the information of the object as an ostream.
     */
    friend std::ostream &operator<<(std::ostream &stream, Ray const &ray) {
        return stream << "Ray of initPt: " << ray.initPt << " and direction: " << ray.dir;
    }
};

#pragma once

#include <glm/vec3.hpp>

#include "utils.hpp"

//!  The Ray Object class.
/*!
  The object ray is caracterized by an initial point and a direction
*/
struct Ray {
protected:
    //! A public variable.
    /*!
      pos is the 3D initial point.
    */
    glm::vec3 initPt;

    //! A public variable.
    /*!
      dir is the direction of the ray.
    */
    glm::vec3 dir;

    //! A public variable.
    /*!
      The color of the ray. Each element of the vec3 is contained in [0, 1].
     */
    glm::vec3 color;

public:
    glm::vec3 getInitPt() const { return this->initPt; }
    glm::vec3 getDir() const { return this->dir; }
    glm::vec3 getColor() const { return this->color; }

    glm::vec3 setInitPt(glm::vec3 initPt) { this->initPt = initPt; }
    glm::vec3 setDir(glm::vec3 dir) { this->dir = dir; }
    glm::vec3 setColor(glm::vec3 color) { this->color = color; }
    //! The default constructor.
    /*!
      It creates a ray starting at 0,0,0 and going towards increasing x.
    */
    Ray() : initPt(glm::vec3(0, 0, 0)), dir(glm::vec3(1, 0, 0)) {}

    //! The specialized constructor.
    /*!
      It creates a Ray with specified initial point and direction.
    */
    Ray(glm::vec3 initPt, glm::vec3 dir) : initPt(initPt), dir(glm::normalize(dir)) {}

    void biais(glm::vec3 hitNormal, float biaisCoeff) { initPt = initPt + hitNormal * biaisCoeff; }

    //! An overload of the operator << to print rays for debug.
    /*!
      \param stream the current ostream.
      \param ray the current ray which needs to be printed.
      \return The information of the object as an ostream.
    */
    friend std::ostream &operator<<(std::ostream &stream, Ray const &ray) {
        return stream << "Ray of initPt: " << ray.initPt << " and direction: " << ray.dir;
    }
};

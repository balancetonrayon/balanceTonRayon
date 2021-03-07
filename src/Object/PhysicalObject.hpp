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

/**
 * @brief The core Object class.
 * @class PhysicalObject
 */
class PhysicalObject {
public:
    /**
     * @brief pos is the 3D location of the object.
     *
     */
    glm::vec3 pos;

    /**
     * @brief Construct a new Physical Object object at (0,0,0) by default.
     *
     * @param pos
     */
    explicit PhysicalObject(glm::vec3 pos = glm::vec3()) : pos(pos) {}

    /**
     * @brief An operator overload to print information for debug
     *
     * @param stream
     * @param obj
     * @return std::ostream&
     */
    friend std::ostream &operator<<(std::ostream &stream, PhysicalObject const &obj) {
        return obj.printInfo(stream);
    }

protected:
    //! A pure virtual function returning the information about an object.
    /**
      @param os the current ostream.
      @return the information of the object as an ostream
    */
    virtual std::ostream &printInfo(std::ostream &os) const = 0;
};

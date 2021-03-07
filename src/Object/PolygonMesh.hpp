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
#include "Polygon.hpp"

class PolygonMesh : public PhysicalObject {
protected:
    /**
     * @brief
     *
     */
    std::vector<Polygon> polygons;

public:
    /**
     * @brief
     *
     * @return std::vector<Polygon>::iterator
     */
    std::vector<Polygon>::iterator begin() { return polygons.begin(); }

    /**
     * @brief
     *
     * @return std::vector<Polygon>::iterator
     */
    std::vector<Polygon>::iterator end() { return polygons.end(); }

    /**
     * @brief
     *
     * @param poly
     */
    void addPolygon(const Polygon &poly) { polygons.push_back(poly); }

protected:
    //! @brief A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

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
#include "Triangle.hpp"

class Polygon : public PhysicalObject {
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoordinates;
    glm::vec3 normal;

    /**
     * @brief Add a vertex to the polygon
     *
     * @param vertex
     */
    void addVertex(const glm::vec3 &vertex) { vertices.push_back(vertex); }

    /**
     * @brief add texture of the polygon
     *
     * @param texture
     */
    void addTexture(const glm::vec2 &texture) { textureCoordinates.push_back(texture); }

    /**
     * @brief Set the Normal of the polygon
     *
     * @param n
     */
    void setNormal(const glm::vec3 &n) { normal = n; }

    /**
     * @brief Method which transforms a polygon into n-2 triangles (if n is the number of vertices)
     *
     * @param triangles the output triangles
     */
    void polygon2Triangle(const std::vector<Triangle> &triangles);

protected:
    //! @brief A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

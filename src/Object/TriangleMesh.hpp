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
#include "Triangle.hpp"
#include "PolygonMesh.hpp"

class TriangleMesh : public BasicObject {
protected:
    /**
     * @brief
     *
     */
    std::vector<Triangle> triangles;

public:
    void intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                   std::vector<Ray> &rays) const override;

    /**
     * @brief Get the Triangles object
     *
     * @return std::vector<Triangle>
     */
    std::vector<Triangle> getTriangles() const { return this->triangles; }

    //! Public method
    /**
        @brief Move the center of the mesh to the position
        @param position new position of the center of the Triangle mesh
    */
    void offset(const glm::vec3 &position) const {
        for (Triangle triangle : triangles) {
            triangle.offset(position);
        }
    }
    //! A specialized constructor.
    /**
     * @brief Construct a new Triangle Mesh with the help of a polygon mesh.
     *
     * @param polyMesh
     */
    explicit TriangleMesh(PolygonMesh &polyMesh) {
        reflexionIndex = 0;
        refractiveIndex = 0;
        transparency = 0;
        albedo = 0.18;
        for (Polygon poly : polyMesh) {
            std::vector<Triangle> polygonTriangles;
            int verticeNb = poly.vertices.size();
            for (int id = 1; id < verticeNb - 1; ++id) {
                polygonTriangles.push_back(Triangle(poly.vertices[0], poly.vertices[id],
                                                    poly.vertices[id + 1], poly.normal));
            }
            triangles.insert(triangles.end(), polygonTriangles.begin(), polygonTriangles.end());
        }
    }

protected:
    //! @brief A normal membser taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

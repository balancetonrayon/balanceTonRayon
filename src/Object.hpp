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

//!
/**
 * @brief The core Object class.
 * @class PhysicalObject
 */
class PhysicalObject {
public:
    //! A public variable.
    /**
      @brief pos is the 3D location of the object.
    */
    glm::vec3 pos;

    //! The default constructor.
    /**
      It puts the object in (0,0,0).
    */
    explicit PhysicalObject(glm::vec3 pos = glm::vec3()) : pos(pos) {}

    /**
     * @brief
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

//!  The Light Object class.
/**
  The object represents a light-source, which is located at pos.
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

//!  The SpotLight class.
/**
  It represents a light which intensity decreases with the square of the distance
*/
class SpotLight : public Light {
public:
    void outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const override;

    /**
     * @brief Construct a new Spot Light at (0, 0, 0), and selects (0, 0, 0) as the color of the
      source by default
     *
     * @param pos
     * @param color
     * @param i
     */
    explicit SpotLight(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                       float i = 100)
        : Light(pos, color, i) {}
};

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

/**
    \class Inter
  @brief This class contains all the information of an intersection.
*/
class Inter {
public:
    //! A public variable.
    /**

        @brief if is the distance between the intersection and the object.
    */
    float id;

    //! A public variable.
    /**
      @brief ld is the distance between the intersection and the light.
    */
    float ld;

    //! A public variable.
    /**
      @brief normal is the normal at the intersection.
    */
    glm::vec3 normal;

    //! A public variable.
    /**
      @brief rColor is the color of the ray at the intersection
    */
    glm::vec3 rColor;

    //! A public variable.
    /**
      @brief objColor is the color of the object responsible for the intersection
    */
    glm::vec3 objColor;

    //! A public variable
    /**
      @brief The reflexion index of the object responsible for intersection
    */
    float objReflexionIndex;

    //! A public variable
    /**
      @brief The transparency of the object responsible for intersection
    */
    float objTransparency;

    //! A public variable
    /**
      @brief The albedo of the object responsible for intersection
    */
    float objAlbedo;

    //! The default constructor.
    /**
      @brief The intersection distances are chosen negative and the normal and the color are (0,0,0)
      vectors
    */
    Inter() : id(-1), ld(-1), normal(glm::vec3()), rColor(glm::vec3()){};

    //! The specialized constructor.
    /**
      @brief Creates an intersection with the desired parameters
    */
    explicit Inter(float i, float l, glm::vec3 n, glm::vec3 c)
        : id(i), ld(l), normal(n), rColor(c){};
};

//!  The BasicObject class.
/**
  Every object which has a physical meaning is deriving from this class.
  @sa PhysicalObject
*/
class BasicObject : public PhysicalObject {
public:
    //! A public variable.
    /**
      @brief color represents the color of the light-source. color elements are between
      0 and 1.
    */
    glm::vec3 color;

    //! A public variable.
    /**
      @brief The transparency helps determining how much light is refracted.
    */
    float transparency;

    //! A public variable.
    /**
      @brief The refactive index is used to compute refracted rays
    */
    float refractiveIndex;

    //! A public variable.
    /**
      @brief The reflexion index is the amount of light directly reflected.
    */
    float reflexionIndex;

    //! A public variable.
    /**
      @brief The amount of light which is diffused.
    */
    float albedo;

    virtual std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                                       Inter &inter) const = 0;

    /**
     * @brief Construct a new Basic Object object
     *
     * @param pos
     * @param color
     * @param t
     * @param r
     * @param R
     * @param a
     */
    explicit BasicObject(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                         float t = 0, float r = 1, float R = 1, float a = 0.18)
        : PhysicalObject(pos),
          color(color),
          transparency(t),
          refractiveIndex(r),
          reflexionIndex(R),
          albedo(a) {}
};

//!  The Camera class.
/**
  \class Camera
  @brief It represents and contains all the information about the camera.
*/
class Camera : public PhysicalObject {
public:
    //! A public variable.
    /**
      @brief Normal direction of the camera.
    */
    glm::vec3 dir;

    //! A public variable.
    /**
      @brief Vertical vector of the camera's screen.
      @sa hv
    */
    glm::vec3 vv;

    //! A public variable.
    /**
      @brief Vertical vector of the camera's screen.
      @sa vv
    */
    glm::vec3 hv;
    // Size of the screen
    /**
     * @brief
     *
     */
    float sizeX;
    /**
     * @brief
     *
     */
    float sizeY;

    // Resolution of the screen
    /**
     * @brief
     *
     */
    unsigned resX;
    /**
     * @brief
     *
     */
    unsigned resY;

    /**
     * @brief
     *
     */
    float focalLength;

    /**
     * @brief A normal member taking two arguments and returning the generated ray
     *
     * @param x the number of the x pixel
     * @param y the number of the y pixel
     * @return Ray
     */
    Ray genRay(const float &x, const float &y);

    /**
     * @brief Construct a Camera at (0, 0, 0) with screen of size (1, 1) and (1000, 1000)
      pixels 1 away from the image sensor. The camera is assumed horizontal.
     *
     * @param pos
     * @param dir
     * @param sx
     * @param sy
     * @param rx
     * @param ry
     * @param fL
     */
    explicit Camera(glm::vec3 pos = glm::vec3(), glm::vec3 dir = glm::vec3(1, 0, 0), float sx = 1,
                    float sy = 1, unsigned rx = 1000, unsigned ry = 1000, float fL = 1)
        : PhysicalObject(pos),
          dir(glm::normalize(dir)),
          sizeX(sx),
          sizeY(sy),
          resX(rx),
          resY(ry),
          focalLength(fL) {
        if (dir[2]) std::cout << "Erreur, rotation suivant l'axe vertical interdite" << std::endl;
        vv = glm::vec3(0, 0, -1);
        if (!dir[0]) {
            if (dir[1] > 0) {
                hv = glm::vec3(-1, 0, 0);
            }
            if (dir[1] < 0) {
                hv = glm::vec3(1, 0, 0);
            }
        } else if (!dir[1]) {
            if (dir[0] > 0) {
                hv = glm::vec3(0, 1, 0);
            }
            if (dir[0] < 0) {
                hv = glm::vec3(0, -1, 0);
            }
        } else {
            float y = std::sqrt(1 / (1 + dir[2] * dir[2] / (dir[1] * dir[1])));
            hv = glm::vec3(-dir[2] / dir[1] * y, y, 0);
        }
        // std::cout <<"pos : "<<pos <<std::endl<< vv << std::endl << dir << std::endl << hv <<
        // std::endl;
    }

protected:
    /**
    * @brief  A normal member taking one argument and returning the information about
    an object. It replaces the pure virtual member of PhysicalObject
    * @sa PhysicalObject
    *  @param os the current ostream
    *  @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;

    class pixel_out_of_range {};
};

/**
 * @brief Class representing a solid plane
 * @class Plane
 *
 */
class Plane : public BasicObject {
public:
    /**
     * @brief The normal vector of the plane.
     *
     */
    glm::vec3 normal;
    
    /**
     * @brief The texture of the plane. Must have a getColor method defined.
     * 
     */
    Texture texture;

    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

    /**
     * @brief Construct a Plan of normal (0, 0, 1) and containing (0, 0, 0) by default.
     *
     * @param pos the origin of the plan
     * @param color the colour of the plan if no texture is defined
     * @param normal the normal vector of the plan
     * @param t the transparency of the plan if no texture is defined
     * @param r the reflexion index of the plan
     * @param R the refractive index of the plan
     * @param a the albedo of the plan
     */
    explicit Plane(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                   glm::vec3 normal = glm::vec3(0, 0, 1), float t = 0, float r = 1, float R = 1,
                   float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), normal(glm::normalize(normal)) {}

protected:
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

//!  The Sphere class.
/**
    \class Sphere
  @brief It represents a solid sphere.
*/
class Sphere : public BasicObject {
public:
    //! A public variable.
    /**
      @brief The radius of the sphere.
    */
    float radius;

    /**
     * @brief
     *
     * @param iRay
     * @param ltSrc
     * @param inter
     * @return std::vector<Ray>
     */
    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

    //! A specialized constructor.
    /**
     * @brief Construct a Sphere at (0, 0, 0) of radius 1 by default.
     *
     * @param pos
     * @param color
     * @param radius
     * @param t
     * @param r
     * @param R
     * @param a
     */
    explicit Sphere(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                    float radius = 1, float t = 0, float r = 1, float R = 1, float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), radius(radius) {}

protected:
    //! @brief A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

class Box : public BasicObject {
public:
    glm::vec3 pos1;
    glm::vec3 pos2;
    glm::vec3 pos3;

    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

    /**
     * @brief Construct a new Box object
     *
     * @param v0
     * @param v1
     * @param v2
     * @param v3
     * @param color
     * @param t
     * @param r
     * @param R
     * @param a
     */
    explicit Box(glm::vec3 v0 = glm::vec3(), glm::vec3 v1 = glm::vec3(), glm::vec3 v2 = glm::vec3(),
                 glm::vec3 v3 = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1), float t = 0,
                 float r = 1, float R = 1, float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), pos1(pos1), pos2(pos2), pos3(pos3) {}

protected:
    //! @brief A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

/**
  \class Triangle
  @brief It represents a solid triangle.
*/
class Triangle : public BasicObject {
public:
    //! A public variable.
    /**
      @brief The second vertice of the triangle.
    */
    glm::vec3 pos1;

    //! A public variable.
    /**
     @brief  The third vertice of the triangle.
    */
    glm::vec3 pos2;

    //! A public variable.
    /**
      @brief The normal of the triangle.
    */
    glm::vec3 normal;

    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

    /**
     * @brief
     *
     * @param position
     */
    void offset(const glm::vec3 &position) {
        pos = pos + position;
        pos1 = pos1 + position;
        pos2 = pos2 + position;
    }

    //! A specialized constructor.

    /**
     * @brief Construct a new Triangle object
     *
     * @param v0
     * @param v1
     * @param v2
     * @param n
     * @param color
     * @param t
     * @param r
     * @param R
     * @param a
     */
    explicit Triangle(glm::vec3 v0 = glm::vec3(), glm::vec3 v1 = glm::vec3(),
                      glm::vec3 v2 = glm::vec3(), glm::vec3 n = glm::vec3(1, 1, 1),
                      glm::vec3 color = glm::vec3(1, 1, 1), float t = 0, float r = 0, float R = 0,
                      float a = 0.18)
        : BasicObject(v0, color, t, r, R, a), pos1(v1), pos2(v2), normal(glm::normalize(n)) {
        if (n.x == 1 && n.y == 1 && n.z == 1) normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
    }

protected:
    //! @brief A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
      @param os the current ostream
      @return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

// class AccelerationStructure : public Box {};

class Polygon : public PhysicalObject {
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoordinates;
    glm::vec3 normal;

    /**
     * @brief
     *
     * @param vertice
     */
    void addVertice(const glm::vec3 &vertice) { vertices.push_back(vertice); }

    /**
     * @brief
     *
     * @param texture
     */
    void addTexture(const glm::vec2 &texture) { textureCoordinates.push_back(texture); }

    /**
     * @brief Set the Normal object
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

class TriangleMesh : public BasicObject {
protected:
    /**
     * @brief
     *
     */
    std::vector<Triangle> triangles;

public:
    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

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
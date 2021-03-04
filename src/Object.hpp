#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <memory>
#include <vector>

#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>

#include "Ray.hpp"

//!  The core Object class.
/*!
  Every object which has a physical meaning is deriving from this class.
*/
class PhysicalObject {
public:
    //! A public variable.
    /*!
      pos is the 3D location of the object.
    */
    glm::vec3 pos;

    //! The default constructor.
    /*!
      It puts the object in (0,0,0).
    */
    explicit PhysicalObject(glm::vec3 pos = glm::vec3()) : pos(pos) {}

    friend std::ostream &operator<<(std::ostream &stream, PhysicalObject const &obj) {
        return obj.printInfo(stream);
    }

protected:
    //! A pure virtual function returning the information about an object.
    /*!
      \param os the current ostream.
      \return the information of the object as an ostream
    */
    virtual std::ostream &printInfo(std::ostream &os) const = 0;
};

//!  The Light Object class.
/*!
  The object represents a light-source, which is located at pos.
*/
class Light : public PhysicalObject {
public:
    //! A public variable.
    /*!
      color represents the color of the light-source. color elements are between
      0 and 1.
    */
    glm::vec3 color;

    //! A public variable.
    /*!
      intensity represents the color of the light-source. color elements are
      between 0 and 1.
    */
    float intensity;

    //! A pure virtual function completing the ray going from the intersect
    //! point to the light source.
    /*!
      \param hitPt the intersection point
      \return the resulting rays
    */
    virtual std::vector<Ray> outboundRays(glm::vec3 hitPt) const = 0;

    //! The default constructor.
    /*!
      It puts the object in (0, 0, 0), and selects (0, 0, 0) as the color of the
      source.
    */
    explicit Light(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1), float i = 1)
        : PhysicalObject(pos), color(color), intensity(i) {}

protected:
    //! A normal member taking one argument and returning the information about
    //! an object.
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

//!  The DirectLight class.
/*!
  It represents a light which is infinetely far.
*/
class DirectLight : public Light {
public:
    std::vector<Ray> outboundRays(const glm::vec3 hitPt) const override;

    //! The default constructor.
    /*!
      It puts the object in (0, 0, 0), and selects (0, 0, 0) as the color of the
      source.
    */
    explicit DirectLight(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                         float i = 2000)
        : Light(pos, color, i) {}
};

//!  The SpotLight class.
/*!
  It represents a light which intensity decreases with the square of the distance
*/
class SpotLight : public Light {
public:
    std::vector<Ray> outboundRays(const glm::vec3 hitPt) const override;

    //! The default constructor.
    /*!
      It puts the object in (0, 0, 0), and selects (0, 0, 0) as the color of the
      source.
    */
    explicit SpotLight(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                       float i = 100)
        : Light(pos, color, i) {}
};

//!  The AreaLight class.
/*!
  \class AreaLight
  \brief Statistical Area Light
  It represents a light which intensity decreases with the square of the distance
*/
class AreaLight : public Light {
protected:
    int numberOfRays;
    glm::vec3 vv;
    glm::vec3 hv;

public:
    std::vector<Ray> outboundRays(const glm::vec3 hitPt) const override;

    //! The default constructor.
    /*!
      It puts the object in (0, 0, 0), and sets the color of the
      source as white.
    */
    explicit AreaLight(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                       float i = 10000, int n = 64)
        : Light(pos, color, i), numberOfRays(n) {}
};

//!  The Inter class.
/*!
  This class contains all the information of an intersection.
*/
class Inter {
public:
    //! A public variable.
    /*!
      if is the distance between the intersection and the object.
    */
    float id;

    //! A public variable.
    /*!
      ld is the distance between the intersection and the light.
    */
    float ld;

    //! A public variable.
    /*!
      normal is the normal at the intersection.
    */
    glm::vec3 normal;

    //! A public variable.
    /*!
      color is the color of the ray at the intersection
    */
    glm::vec3 rColor;

    glm::vec3 objColor;

    //! A public variable
    /*!
      the reflexion Index of the intersection
    */
    float objReflexionIndex;

    //! A public variable
    /*!

    */
    float objTransparency;

    float objAlbedo;

    Inter() : id(-1), ld(-1), normal(glm::vec3()), rColor(glm::vec3()){};

    explicit Inter(float i, float l, glm::vec3 n, glm::vec3 c)
        : id(i), ld(l), normal(n), rColor(c){};
};

//!  The BasicObject class.
/*!
  Every object which has a physical meaning is deriving from this class.
  \sa PhysicalObject
*/
class BasicObject : public PhysicalObject {
public:
    //! A public variable.
    /*!
      color represents the color of the light-source. color elements are between
      0 and 1.
    */
    glm::vec3 color;

    //! A public variable.
    /*!
      The transparency helps determining how much light is refracted.
    */
    float transparency;

    //! A public variable.
    /*!
      The refactive index is used to compute refracted rays
    */
    float refractiveIndex;

    //! A public variable.
    /*!
      The reflexion index is the amount of light directly reflected.
    */
    float reflexionIndex;

    //! A public variable.
    /*!
      The amount of light which is diffused.
    */
    float albedo;

    virtual std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                                       Inter &inter) const = 0;

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
/*!
  \class Camera
  It represents and contains all the information about the camera.
*/
class Camera : public PhysicalObject {
public:
    //! A public variable.
    /*!
      Normal direction of the camera.
    */
    glm::vec3 dir;

    //! A public variable.
    /*!
      Vertical vector of the camera's screen.
      \sa hv
    */
    glm::vec3 vv;

    //! A public variable.
    /*!
      Vertical vector of the camera's screen.
      \sa vv
    */
    glm::vec3 hv;
    // Size of the screen
    float sizeX;
    float sizeY;

    // Resolution of the screen
    unsigned resX;
    unsigned resY;

    float focalLength;

    //! A normal member taking two arguments and returning the generated ray
    /*!
      \param x the number of the x pixel
      \param y the number of the y pixel
      \return the generated ray
    */
    Ray genRay(unsigned x, unsigned y) noexcept;

    //! The default constructor.
    /*!
      Creates a Camera at (0, 0, 0) with screen of size (1, 1) and (1000, 1000)
      pixels 1 away from the image sensor. The camera is assumed horizontal.
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
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;

    class pixel_out_of_range {};
};

//!  The Plane class.
/*!
  It represents a solid plane.
*/
class Plane : public BasicObject {
public:
    //! A public variable.
    /*!
      The normal vector of the plane.
    */
    glm::vec3 normal;  //

    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

    //! The default constructor.
    /*Creates a Plan of normal (0, 0, 1) and containing (0, 0, 0) by default.
     */
    explicit Plane(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                   glm::vec3 normal = glm::vec3(0, 0, 1), float t = 0, float r = 1, float R = 1,
                   float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), normal(glm::normalize(normal)) {}

protected:
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

//!  The Sphere class.
/*!
  It represents a solid sphere.
*/
class Sphere : public BasicObject {
public:
    //! A public variable.
    /*!
      The radius of the sphere.
    */
    float radius;

    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

    //! A specialized constructor.
    /*!
      Creates a Sphere in (0, 0, 0) of radius 1 by default.
    */
    explicit Sphere(glm::vec3 pos = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1),
                    float radius = 1, float t = 0, float r = 1, float R = 1, float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), radius(radius) {}

protected:
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
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

    explicit Box(glm::vec3 v0 = glm::vec3(), glm::vec3 v1 = glm::vec3(), glm::vec3 v2 = glm::vec3(),
                 glm::vec3 v3 = glm::vec3(), glm::vec3 color = glm::vec3(1, 1, 1), float t = 0,
                 float r = 1, float R = 1, float a = 0.18)
        : BasicObject(pos, color, t, r, R, a), pos1(pos1), pos2(pos2), pos3(pos3) {}

protected:
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};
//!  The Triangle class.
/*!
  It represents a solid triangle.
*/
class Triangle : public BasicObject {
public:
    //! A public variable.
    /*!
      The second vertice of the triangle.
    */
    glm::vec3 pos1;

    //! A public variable.
    /*!
      The third vertice of the triangle.
    */
    glm::vec3 pos2;

    //! A public variable.
    /*!
      The normal of the triangle.
    */
    glm::vec3 normal;

    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

    void offset(glm::vec3 position) {
        pos = pos + position;
        pos1 = pos1 + position;
        pos2 = pos2 + position;
    }

    //! A specialized constructor.
    /*!
      Creates a Triangle
    */
    explicit Triangle(glm::vec3 v0 = glm::vec3(), glm::vec3 v1 = glm::vec3(),
                      glm::vec3 v2 = glm::vec3(), glm::vec3 n = glm::vec3(1, 1, 1),
                      glm::vec3 color = glm::vec3(1, 1, 1), float t = 0, float r = 0, float R = 0,
                      float a = 0.18)
        : BasicObject(v0, color, t, r, R, a), pos1(v1), pos2(v2), normal(glm::normalize(n)) {
        if (n.x == 1 && n.y == 1 && n.z == 1) normal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
    }

protected:
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

// class AccelerationStructure : public Box {};

class Polygon : public PhysicalObject {
public:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoordinates;
    glm::vec3 normal;

    void addVertice(glm::vec3 vertice) { vertices.push_back(vertice); }
    void addTexture(glm::vec2 texture) { textureCoordinates.push_back(texture); }
    void setNormal(glm::vec3 n) { normal = n; }

    void polygon2Triangle(std::vector<Triangle> triangles) {}

protected:
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

class PolygonMesh : public PhysicalObject {
protected:
    std::vector<Polygon> polygons;

public:
    std::vector<Polygon>::iterator begin() { return polygons.begin(); }

    std::vector<Polygon>::iterator end() { return polygons.end(); }

    void addPolygon(Polygon poly) { polygons.push_back(poly); }

protected:
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

class TriangleMesh : public BasicObject {
protected:
    std::vector<Triangle> triangles;

public:
    std::vector<Ray> intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc,
                               Inter &inter) const override;

    std::vector<Triangle> getTriangles() { return this->triangles; }

    //! Public method
    /*!
        Move the center of the mesh to the position
        @param position new position of the center of the Triangle mesh
    */
    void offset(glm::vec3 position) {
        for (Triangle triangle : triangles) {
            triangle.offset(position);
        }
    }
    //! A specialized constructor.
    /*!
      Creates a Mesh made of triangles from a mesh made of polygons
    */
    explicit TriangleMesh(PolygonMesh polyMesh) {
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
    //! A normal membser taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const override;
};

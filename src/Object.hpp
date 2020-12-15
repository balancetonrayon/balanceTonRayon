#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <vector>
#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <algorithm>
#include "Ray.hpp"

//!  The core Object class.
/*!
  Every object which has a physical meaning is deriving from this class.
*/
struct PhysicalObject
{
    //! A public variable.
    /*!
      pos is the 3D location of the object.
    */
    glm::vec3 pos;

    //! A pure virtual function returning the information about an object.
    /*!
      \param os the current ostream.
      \return the information of the object as an ostream
    */
    virtual std::ostream &printInfo(std::ostream &os) const = 0;

    //! The default constructor.
    /*!
      It puts the object in (0,0,0).
    */
    explicit PhysicalObject(glm::vec3 pos = glm::vec3()) : pos(pos) {}

    friend std::ostream &operator<<(std::ostream &stream, PhysicalObject const &obj)
    {
        return obj.printInfo(stream);
    }
};

//!  The light-source Object class.
/*!
  The object represents a light-source, which is located at pos.
*/
struct Light : public PhysicalObject
{

    //! A public variable.
    /*!
      color represents the color of the light-source. color elements are between 0 and 1.
    */
    cv::Vec3b color;

    //! A public variable.
    /*!
      intensity represents the color of the light-source. color elements are between 0 and 1.
    */
    float intensity;

    //! A normal member taking one argument and returning the information about an object.
    /*!
      \param os the current ostream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const;

    //! A pure virtual function completing the ray going from the intersect point to the light source.
    /*!
      \param hitPt the intersection point
      \param ray the ray going from the intersection point to the light source passed as reference
      \param rayColor the color of the ray (vector of elements between 0 and 1) passed as reference
      \return the distance between the intersection and the source 
    */
    virtual float outboundRay(const glm::vec3 hitPt, Ray &ray, cv::Vec3b &rayColor) const = 0;

    //! The default constructor.
    /*!
      It puts the object in (0, 0, 0), and selects (0, 0, 0) as the color of the source.
    */
    explicit Light(glm::vec3 pos = glm::vec3(), cv::Vec3b color = cv::Vec3b(1, 1, 1), float i = 1) : PhysicalObject(pos),
                                                                                                     color(color), intensity(i)
    {
    }
};

struct DirectLight : public Light
{
    float outboundRay(const glm::vec3 hitPt, Ray &ray, cv::Vec3b &rayColor) const;

    //! The default constructor.
    /*!
      It puts the object in (0, 0, 0), and selects (0, 0, 0) as the color of the source.
    */
    explicit DirectLight(glm::vec3 pos = glm::vec3(), cv::Vec3b color = cv::Vec3b(1, 1, 1), float i = 3) : Light(pos, color, i) {}
};

struct SpotLight : public Light
{
    float outboundRay(const glm::vec3 hitPt, Ray &ray, cv::Vec3b &rayColor) const;

    //! The default constructor.
    /*!
      It puts the object in (0, 0, 0), and selects (0, 0, 0) as the color of the source.
    */
    explicit SpotLight(glm::vec3 pos = glm::vec3(), cv::Vec3b color = cv::Vec3b(1, 1, 1), float i = 10000) : Light(pos, color, i) {}
};

struct ObjectBase : public PhysicalObject
{
    //! A public variable.
    /*!
      color represents the color of the light-source. color elements are between 0 and 1.
    */
    cv::Vec3b color;

    float transparency;
    float refractiveIndex;
    float reflexionIndex;
    float albedo;

    virtual std::vector<Ray> intersect(const Ray ray, const std::shared_ptr<Light> ltSrc, float &iDistance, float &lDistance, glm::vec3 &normal, cv::Vec3b &rColor) = 0;

    explicit ObjectBase(glm::vec3 pos = glm::vec3(), cv::Vec3b color = cv::Vec3b(1, 1, 1), float t = 0, float r = 1, float R = 1, float a = 0.18) : PhysicalObject(pos), color(color), transparency(t), refractiveIndex(r), reflexionIndex(R), albedo(a)
    {
        std::cout << pos << std::endl;
    }
    //explicit ObjectBase(glm::vec3 pos, float t, float r, float a) : PhysicalObject(pos), transparency(t), refractiveIndex(r), albedo(a) {}
};

struct Camera : public PhysicalObject
{
    //! A public variable.
    /*!
      Direction of the camera.
    */
    glm::vec3 dir;

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
      \return the number of the y pixel
    */
    Ray genRay(unsigned x, unsigned y);

    //! A normal member taking one argument and returning the information about an object.
    /*!
      \param os the current osstream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const;

    //! The default constructor.
    /*!
      Creates a Camera at (0, 0, 0) with screen of size (1, 1) and (1000, 1000) pixels 1 away from the image sensor.
    */
    explicit Camera(glm::vec3 pos = glm::vec3(), float sx = 1, float sy = 1, unsigned rx = 1000, unsigned ry = 1000, float fL = 1) : PhysicalObject(pos), sizeX(sx), sizeY(sy),
                                                                                                                                     resX(rx), resY(ry), focalLength(fL) {}
};

struct Plane : public ObjectBase
{
    //! A public variable.
    /*!
      The normal vector of the plane
    */
    glm::vec3 normal; //

    std::vector<Ray> intersect(const Ray ray, const std::shared_ptr<Light> ltSrc, float &iDistance, float &lDistance, glm::vec3 &normal, cv::Vec3b &rColor);

    //! A normal member taking one argument and returning the information about an object.
    /*!
      \param os the current osstream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const;

    //! The default constructor.
    /*Creates a Plan of normal (0, 0, 1) and containing (0, 0, 0) by default.
    */
    explicit Plane(glm::vec3 pos = glm::vec3(), cv::Vec3b color = cv::Vec3b(1, 1, 1), glm::vec3 normal = glm::vec3(0, 0, 1), float t = 0, float r = 1, float R = 1, float a = 0.18) : ObjectBase(pos, color, t, r, R, a), normal(glm::normalize(normal)) {}
};

struct Sphere : public ObjectBase
{
    //! A public variable.
    /*!
      The radius of the sphere
    */
    float radius;

    std::vector<Ray> intersect(const Ray ray, const std::shared_ptr<Light> ltSrc, float &iDistance, float &lDistance, glm::vec3 &normal, cv::Vec3b &rColor);

    //! A normal member taking one argument and returning the information about an object.
    /*!
      \param os the current osstream
      \return The information of the object as an ostream
    */
    std::ostream &printInfo(std::ostream &os) const;

    //! The default constructor.
    /*!
      Creates a Sphere in (0, 0, 0) of radius 1 by default.
    */
    explicit Sphere(glm::vec3 pos = glm::vec3(), cv::Vec3b color = cv::Vec3b(1, 1, 1), float radius = 1, float t = 0, float r = 1, float R = 1, float a = 0.18) : ObjectBase(pos, color, t, r, R, a), radius(radius) {}
};

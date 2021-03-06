/**
 * @file RayTracer.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief
 * @version 0.1
 * @date 2021-03-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <exception>

#include "Scene.hpp"

class StdRayTracer {
public:
    void render(Scene scene);
};

/**
 * @brief
 *
 */
class FixedAntiAliasingRayTracer {
protected:
    /**
     * @brief
     *
     */
    int sqrtAAPower;

public:
    /**
     * @brief
     *
     * @return int
     */
    int getAAPower() { return this->sqrtAAPower; }
    /**
     * @brief
     *
     * @param pow
     */
    void setAAPower(int pow) { this->sqrtAAPower = pow; }

    /**
     * @brief
     *
     * @param scene
     */
    void render(Scene scene);

    /**
     * @brief Construct a new Fixed Anti Aliasing Ray Tracer object
     *
     */
    explicit FixedAntiAliasingRayTracer() : sqrtAAPower(4) {}
    /**
     * @brief Construct a new Fixed Anti Aliasing Ray Tracer object
     *
     * @param pow
     */
    explicit FixedAntiAliasingRayTracer(int pow) { this->sqrtAAPower = pow; }
};

/*class StochasticAntiAliasingRayTracer {
protected:
    int minSteps;

public:

    void render(Scene scene);
};*/

/**
 * @brief
 *
 */
class SuperSampler {};

/**
 * @brief Fresnel function as explained here :
 * https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
 * ior is the refraction index of the material of the physical object the ray has either hit or is
 * about to leave (glass, water, etc.)
 *
 * @param iRay
 * @param normal
 * @param refractionIndex
 * @return float
 */
float fresnel(Ray iRay, const glm::vec3 &normal, const float &refractionIndex);

/**
 * @brief
 *
 * @param iRay
 * @param normal
 * @param refractionIndex
 * @return glm::vec3
 */
glm::vec3 refract(const Ray &iRay, const glm::vec3 &normal, const float &refractionIndex);

/**
 * @brief
 *
 * @param ray
 * @param lightSource
 * @param objects
 * @param backgroundColor
 * @param depth
 * @return glm::vec3
 */
glm::vec3 castRay(Ray const &ray, std::shared_ptr<Light> const &lightSource,
                  std::vector<std::shared_ptr<BasicObject>> const &objects,
                  const glm::vec3 &backgroundColor, const int &depth);
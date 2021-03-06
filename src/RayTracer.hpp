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

class RayTracer {
protected:
    /**
     * @brief This boolean memorizes wether the ray tracer should adapt the luminosity at the end of
     * the day or not
     *
     */
    bool adaptation;

public:
    /**
     * @brief Pure virtual method - The main method of the ray tracer. Renders a 3D scene ans saves
     * the image.
     *
     * @param scene
     */
    virtual void render(const Scene &scene) const = 0;
};

/**
 * @brief Standard ray tracer engine.
 *
 */
class StdRayTracer : public RayTracer {
public:
    /**
     * @brief
     *
     * @param scene
     */
    void render(const Scene &scene) const override;
};

/**
 * @brief Standard ray tracer engine with jitter AntiAliasing.
 *
 */
class FixedAntiAliasingRayTracer : public RayTracer {
protected:
    /**
     * @brief the square root of the number of rays cast by the engine for each pixel.
     *
     */
    int sqrtAAPower;

public:
    /**
     * @brief Getter: power
     *
     * @return int the power of the AA
     */
    int getAAPower() const { return this->sqrtAAPower; }

    /**
     * @brief Setter: power
     *
     * @param pow the power of the AA
     */
    void setAAPower(const int &pow) { this->sqrtAAPower = pow; }

    /**
     * @brief Renders the scene in 2D with Anti-Aliasing.
     *
     * @param scene
     */
    void render(const Scene &scene) const override;

    /**
     * @brief Construct a new Fixed Anti Aliasing Ray Tracer and set its power to 4.
     *
     */
    explicit FixedAntiAliasingRayTracer() : sqrtAAPower(4) {}

    /**
     * @brief Construct a new Fixed Anti Aliasing Ray Tracer object ans specify its power.
     *
     * @param pow
     */
    explicit FixedAntiAliasingRayTracer(const int &pow) { this->sqrtAAPower = pow; }
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
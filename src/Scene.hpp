/**
 * @file Scene.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief Definition of the Scene class which contains the information of the 3D scene that will be
 * rendered by a raytracer
 * @sa RayTracer.hpp
 * @version 1
 * @date 2021-03-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <memory>
#include <vector>

#include "Object/BasicObject.hpp"
#include "Object/Camera.hpp"

/**
 * @class Scene
 * @brief
 *
 */
class Scene {
    /**
     * @brief The objects contained in the scene
     *
     */
    std::vector<std::shared_ptr<BasicObject>> objects;

    /**
     * @brief The sources of light contained in the scene
     *
     */
    std::vector<std::shared_ptr<Light>> sources;

    /**
     * @brief The camera of the scene
     *
     */
    std::shared_ptr<Camera> camera;

    /**
     * @brief The background color of the scene
     *
     */
    glm::vec3 backgroundColor;

    /**
     * @brief max recursive depth
     *
     */
    int maxDepth;

public:
    /**
     * @brief Get the Background Color of the scene
     *
     * @return glm::vec3
     */
    glm::vec3 getBackgroundColor() const { return this->backgroundColor; }

    /**
     * @brief Get the Max recursive Depth
     *
     * @return int
     */
    int getMaxDepth() const { return maxDepth; }

    /**
     * @brief Set the Background Color of the image
     *
     * @param color
     */
    void setBackgroundColor(glm::vec3 color) { this->backgroundColor = color; }

    void setMaxDepth(int depth) { this->maxDepth = depth; }

    /**
     * @brief Get the pointers of the objects of the scene
     *
     * @return std::shared_ptr<BasisObject>
     */

    auto getObjects() const { return objects; }

    /**
     * @brief Get the pointers of the light sources of the scene
     *
     * @return std::shared_ptr<LightSource>
     */
    auto getSources() const { return sources; }

    /**
     * @brief Get a pointer of the camera of the scene
     *
     * @return auto
     */
    auto getCamera() const { return camera; }

    /**
     * @brief Add an object to the scene
     *
     * @param object
     */
    void addObject(const std::shared_ptr<BasicObject> &object) { objects.push_back(object); }

    /**
     * @brief Add a light source to the scene
     *
     * @param source
     */
    void addSource(const std::shared_ptr<Light> &source) { sources.push_back(source); }

    /**
     * @brief Set the camera of the scene
     *
     * @param camera
     */
    void setCamera(const std::shared_ptr<Camera> &camera) { this->camera = camera; }

    /** The default constructor.
    /**
     * @brief Construct a scene, setting no background color (the background will be black by
    default)
     *
     */
    explicit Scene() : backgroundColor(glm::vec3(0, 0, 0)) {}

    /** A specialized constructor.
    /**
     * @brief Construct a scene, specifiying the backgroundColor.
     *
     * @param color
     */
    explicit Scene(glm::vec3 color) : backgroundColor(color) {}
};

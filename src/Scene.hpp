/**
 * @file Scene.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief
 * @version 0.1
 * @date 2021-03-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <memory>
#include <vector>

#include "Object.hpp"
/**
 * @class Scene
 * @brief
 *
 */
class Scene {
    /**
     * @brief
     *
     */
    std::vector<std::shared_ptr<BasicObject>> objects;
    /**
     * @brief
     *
     */
    std::vector<std::shared_ptr<Light>> sources;
    /**
     * @brief
     *
     */
    std::shared_ptr<Camera> camera;
    /**
     * @brief
     *
     */
    glm::vec3 backgroundColor;

public:
    /**
     * @brief Get the Objects object
     *
     * @return auto
     */
    auto getObjects() const { return objects; }
    /**
     * @brief Get the Sources object
     *
     * @return auto
     */
    auto getSources() const { return sources; }
    /**
     * @brief Get the Camera object
     *
     * @return auto
     */
    auto getCamera() const { return camera; }
    /**
     * @brief Get the Color object
     *
     * @return glm::vec3
     */
    glm::vec3 getColor() { return backgroundColor; }
    /**
     * @brief
     *
     * @param object
     */
    void addObject(std::shared_ptr<BasicObject> object) { objects.push_back(object); }
    /**
     * @brief
     *
     * @param source
     */
    void addSource(std::shared_ptr<Light> source) { sources.push_back(source); }

    /**
     * @brief Set the Camera object
     *
     * @param camera
     */
    void setCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }

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

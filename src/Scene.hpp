#pragma once

#include <memory>
#include <vector>

#include "Object.hpp"

class Scene {
    std::vector<std::shared_ptr<BasicObject>> objects;

    std::vector<std::shared_ptr<Light>> sources;

    std::shared_ptr<Camera> camera;

    glm::vec3 backgroundColor;

public:
    auto getObjects() const { return objects; }
    auto getSources() const { return sources; }
    auto getCamera() const { return camera; }
    glm::vec3 getColor() { return backgroundColor; }

    void addObject(std::shared_ptr<BasicObject> object) { objects.push_back(object); }

    void addSource(std::shared_ptr<Light> source) { sources.push_back(source); }

    void setCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }

    //! A specialized constructor.
    /*!
      Creates a scene, setting no background color (the background will be black by default)
    */
    explicit Scene() : backgroundColor(glm::vec3(0, 0, 0)) {}

    //! A specialized constructor.
    /*!
      Creates a scene, specifiying the backgroundColor
    */
    explicit Scene(glm::vec3 color) : backgroundColor(color) {}
};

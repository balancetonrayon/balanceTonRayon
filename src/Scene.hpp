#pragma once

#include <memory>
#include <vector>

#include "Object.hpp"

class Scene {
    std::vector<std::shared_ptr<BasicObject>> objects;

    std::vector<std::shared_ptr<Light>> sources;

    std::shared_ptr<Camera> camera;

public:
    auto getObjects() const { return objects; }
    auto getSources() const { return sources; }
    auto getCamera() const { return camera; }

    void addObject(std::shared_ptr<BasicObject> object) { objects.push_back(object); }

    void addSource(std::shared_ptr<Light> source) { sources.push_back(source); }

    void setCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }

};

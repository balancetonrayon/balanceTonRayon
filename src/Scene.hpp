#pragma once

#include <memory>
#include "Object.hpp"

class Scene
{
    std::vector<std::shared_ptr<PhysicalObject>> objects;

    std::vector<std::shared_ptr<LightSource>> sources;

    std::shared_ptr<Camera> camera;

public:
    auto getObjects() const { return objects; }
    auto getSources() const { return sources; }
    auto getCamera() const { return camera; }
    
    void addObject(std::shared_ptr<PhysicalObject> object)
    {
        objects.push_back(object);
    }
    
    void addSource(std::shared_ptr<LightSource> source)
    {
        sources.push_back(source);
    }
    
    void setCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }
};

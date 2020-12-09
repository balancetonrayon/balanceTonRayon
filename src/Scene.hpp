#pragma once

#include <memory>
#include "RayTracer.hpp"
#include "Object.hpp"

class Scene
{
    std::vector<std::shared_ptr<ObjectBase>> objects;

    std::vector<std::shared_ptr<LightSource>> sources;

    std::shared_ptr<Camera> camera;
    
    RayTracer rt;

public:
    auto getObjects() const { return objects; }
    auto getSources() const { return sources; }
    auto getCamera() const { return camera; }
    
    void addObject(std::shared_ptr<ObjectBase> object)
    {
        objects.push_back(object);
    }
    
    void addSource(std::shared_ptr<LightSource> source)
    {
        sources.push_back(source);
    }
    
    void setCamera(std::shared_ptr<Camera> camera) { this->camera = camera; }
    
    void render();
};

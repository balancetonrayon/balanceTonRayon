#pragma once
#include "Object.hpp"

class Scene
{
    std::vector<PhysicalObject> objects;

    std::vector<LightSource> sources;

    Camera camera;

public:
    auto getObjects() { return objects; }
    auto getSources() { return sources; }
    auto getCamera() { return camera; }

    void add(const Camera &cam)
    {
        camera = cam;
    }

    void add(const LightSource &LSrc)
    {
        sources.push_back(LSrc);
    }

    void add(const ObjectBase &object)
    {
        objects.push_back(object);
    }
};

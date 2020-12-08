#pragma once

#include "Object.hpp"

class Scene
{
    std::vector<PhysicalObject> objects;
    
    LightSource source;
    
    Camera camera;

public:    
    auto getObjects() { return objects; }
    auto getSource() { return source; }
    auto getCamera() { return camera; }
};

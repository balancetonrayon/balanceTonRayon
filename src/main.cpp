#include "Scene.hpp"

int main(int argc, const char **argv)
{
    Scene scene;
    
    auto plane = std::make_shared<Plane>();
    auto camera = std::make_shared<Camera>();
    auto lightSource = std::make_shared<LightSource>();
    
    scene.addObject(plane);
    scene.setCamera(camera);
    scene.addSource(lightSource);
    
    auto objects = scene.getObjects();
    auto sources = scene.getSources();

    std::cout << camera << std::endl;
    std::cout << plane << std::endl;
    std::cout << lightSource << std::endl;

    for (auto object : objects)
    {
        std::cout << *object << std::endl;
    }

    return 0;
}

#include "Scene.hpp"

int main(int argc, const char **argv)
{
    Scene scene;
    Plane plan;
    Camera camera;
    LightSource LSrc;
    scene.add(plan);
    scene.add(camera);
    scene.add(LSrc);
    auto objects = scene.getObjects();
    auto sources = scene.getSources();

    std::cout << camera << std::endl;
    std::cout << plan << std::endl;
    std::cout << LSrc << std::endl;

    for (auto object : objects)
    {
        //std::cout << object << std::endl;
    }

    return 0;
}

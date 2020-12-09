#include "Scene.hpp"

int main(int argc, const char **argv)
{

    Scene scene;

    auto plane = std::make_shared<Plane>();
    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 1), 0.1, 0.1, 11, 11, 0.2);
    auto lightSource = std::make_shared<LightSource>(glm::vec3(5, 0, 10));

    scene.addObject(plane);
    scene.setCamera(camera);
    scene.addSource(lightSource);

    auto objects = scene.getObjects();
    auto sources = scene.getSources();

    cv::mat pixels;
    std::cout << *camera << std::endl;
    for (auto object : objects)
    {
        std::cout << *object << std::endl;
    }

    for (unsigned x = 0; x < camera->resX; ++x)
    {
        for (unsigned y = 0; y < camera->resY; ++y)
        {
            Ray primRay = camera->genRay(x, y);
            std::cout << primRay << std::endl;
            std::vector<Ray> shadowRays;
            for (auto object : objects)
            {
                std::cout << *object << std::endl;
                shadowRays = object->intersect(primRay, *lightSource);
                if (shadowRays.size())
                {
                    std::cout << "Y" << std::endl;
                };
                
            }
        }
    }
    return 0;
}

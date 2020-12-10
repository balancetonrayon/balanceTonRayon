#include "Scene.hpp"

#include <opencv2/opencv.hpp>

void test()
{
    Scene scene;

    auto plane = std::make_shared<Plane>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), 0, 1, 0.18);
    auto sphere1 = std::make_shared<Sphere>(glm::vec3(1, 1.1, 3), glm::vec3(0, 1, 0), 0.25, 0.18);
    auto sphere2 = std::make_shared<Sphere>(glm::vec3(10, 0, 2), glm::vec3(0, 0, 1), 1, 0, 1, 0.18);
    auto sphere3 = std::make_shared<Sphere>(glm::vec3(5, -1.1, 1.5), glm::vec3(1, 0, 1), 1, 0, 1, 0.22);

    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 1.5), 0.1, 0.1, 1000, 1000, 0.05);
    auto lightSource = std::make_shared<LightSource>(glm::vec3(10, 0, 10));
    
    scene.addObject(plane);
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    scene.addObject(sphere1);
    for (auto object : scene.getObjects())
    {
        std::cout << *object << std::endl;
    }
    scene.setCamera(camera);
    scene.addSource(lightSource);

    scene.render();

    cv::waitKey(0);
}

int main(int argc, const char **argv)
{
    test();
    return 0;
}

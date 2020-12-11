#include "Scene.hpp"

#include <opencv2/opencv.hpp>

void test()
{
    Scene scene;

    auto plane = std::make_shared<Plane>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), 0.8, 0.8, 0.8, 0.25);
    auto plane2 = std::make_shared<Plane>(glm::vec3(0, 0, 100), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1), 0.5, 0.5, 0.5, 0.18);
    auto sphere1 = std::make_shared<Sphere>(glm::vec3(11, 0, 2), glm::vec3(0, 1, 0), 1, 0, 1, 0, 0.22);
    auto sphere2 = std::make_shared<Sphere>(glm::vec3(8, 3, 2), glm::vec3(0, 0, 1), 1, 0, 1, 0, 0.22);
    auto sphere3 = std::make_shared<Sphere>(glm::vec3(8, -3, 2), glm::vec3(1, 0, 0), 1, 0, 1, 0, 0.22);

    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 1.5), 0.1, 0.1, 2000, 2000, 0.05);
    auto lightSource = std::make_shared<LightSource>(glm::vec3(8, 0, 0.2));

    scene.addObject(plane);
    //scene.addObject(plane2);
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

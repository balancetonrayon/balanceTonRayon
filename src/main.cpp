#include "Scene.hpp"

#include <opencv2/opencv.hpp>

void test()
{
    Scene scene;

    //auto plane = std::make_shared<Plane>(glm::vec3(10, 10,10), glm::vec3(10, 10,10));
    auto sphere = std::make_shared<Sphere>(glm::vec3(20, 0, 1.5), 2);
    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 1.5), 0.1, 0.1, 2000, 2000, 0.05);
    auto lightSource = std::make_shared<LightSource>(glm::vec3(20, 0, 1000));

    //scene.addObject(plane);
    scene.addObject(sphere);
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

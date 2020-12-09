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

    auto objects = scene.getObjects();
    auto sources = scene.getSources();

    std::cout << *camera << std::endl;
    std::cout << *lightSource << std::endl;
    for (auto object : objects)
    {
        std::cout << *object << std::endl;
    }
    unsigned Y;
    cv::Mat image(cv::Size(camera->resX, camera->resY), CV_8UC3);
    for (unsigned x = 0; x < camera->resX; ++x)
    {
        for (unsigned y = 0; y < camera->resY; ++y)
        {
            Ray primRay = camera->genRay(x, y);
            //std::cout << primRay << std::endl;
            std::vector<Ray> shadowRays;
            for (auto object : objects)
            {

                shadowRays = object->intersect(primRay, *lightSource);
                if (shadowRays.size())
                {
                    //std::cout << *object << std::endl;
                    Y++;
                    cv::Vec3b &color = image.at<cv::Vec3b>(x, y);
                    color[0] = 255;
                    color[1] = 255;
                    color[2] = 255;
                    image.at<cv::Vec3b>(x, y) = color;
                };
            }
        }
    }
    std::cout << Y << std::endl;
    cv::imwrite("name.png", image);
    cv::waitKey(0);
}

int main(int argc, const char **argv)
{
    test();
    return 0;
}

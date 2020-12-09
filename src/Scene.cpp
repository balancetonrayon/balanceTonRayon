#include "Scene.hpp"

#include <opencv2/opencv.hpp>

void Scene::render()
{
    auto lightSource = sources[0];
    
    unsigned Y;
    cv::Mat image(cv::Size(camera->resX, camera->resY), CV_8UC3);
    for (unsigned x = 0; x < camera->resX; ++x)
    {
        for (unsigned y = 0; y < camera->resY; ++y)
        {
            Ray primRay = camera->genRay(x, y);
            std::vector<Ray> shadowRays;
            for (auto object : objects)
            {

                shadowRays = object->intersect(primRay, *lightSource);
                if (shadowRays.size())
                {
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
    
    cv::resize(image, image, cv::Size(500,500));
    cv::imshow("RayTracing", image);
}

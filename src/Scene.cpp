#include "Scene.hpp"

#include <opencv2/opencv.hpp>

void Scene::render()
{
    auto lightSource = sources[0];
    cv::Mat image(cv::Size(camera->resX, camera->resY), CV_8UC3);

    for (unsigned x = 0; x < camera->resX; ++x)
    {
        for (unsigned y = 0; y < camera->resY; ++y)
        {
            Ray primRay = camera->genRay(x, y);
            std::vector<Ray> shadowRays;
            glm::vec3 hitNormal;
            float distance = INFINITY;
            std::shared_ptr<ObjectBase> hitObject = nullptr;
            for (auto object : objects)
            {
                float cDistance;
                shadowRays = object->intersect(primRay, *lightSource, cDistance, hitNormal);
                if (shadowRays.size() && cDistance < distance)
                {
                    hitObject = object;
                    distance = cDistance;
                }
            }
            if (hitObject)
            {
                shadowRays = hitObject->intersect(primRay, *lightSource, distance, hitNormal);
                //std::cout << 0.18 / M_PI * lightSource->intensity * /*lightSource->color **/ std::max(0.f, glm::dot(hitNormal, -primRay.dir)) * 255 << std::endl;
                cv::Vec3b &color = image.at<cv::Vec3b>(x, y);
                color[0] = /*hitObject->albedo*/ 0.18 / M_PI * lightSource->intensity * /*lightSource->color **/ std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255*4;
                color[1] = /*hitObject->albedo*/ 0.18 / M_PI * lightSource->intensity * /*lightSource->color **/ std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255*4;
                color[2] = /*hitObject->albedo*/ 0.18 / M_PI * lightSource->intensity * /*lightSource->color **/ std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255*4;
                image.at<cv::Vec3b>(x, y) = color;
            };
        }
    }

    cv::resize(image, image, cv::Size(1000, 1000));
    cv::imwrite("RayTracing.png", image);
    cv::imshow("RayTracing", image);
}

#include "Scene.hpp"

#include <opencv2/opencv.hpp>

cv::Vec3b castRay(Ray const &ray, std::shared_ptr<LightSource> const &lightSource, std::vector<std::shared_ptr<ObjectBase>> const &objects)
{
    cv::Vec3b color(0, 0, 0);

    std::vector<Ray> shadowRays;
    glm::vec3 hitNormal;
    float distance = INFINITY;
    std::shared_ptr<ObjectBase> hitObject = nullptr;
    for (auto object : objects)
    {
        float cDistance;
        shadowRays = object->intersect(ray, *lightSource, cDistance, hitNormal);
        if (shadowRays.size() && cDistance < distance)
        {
            hitObject = object;
            distance = cDistance;
        }
    }
    if (hitObject)
    {
        //std::cout << "Rayon source: " << ray << std::endl;
        shadowRays = hitObject->intersect(ray, *lightSource, distance, hitNormal);
        //std::cout << "Rayon lumière " << shadowRays[0] << "\n";
        shadowRays[0].initPt[0] = hitNormal[0] * 0.0001 +shadowRays[0].initPt[0];
        shadowRays[0].initPt[1] = hitNormal[1] * 0.0001 +shadowRays[0].initPt[1];
        shadowRays[0].initPt[2] = hitNormal[2] * 0.0001 +shadowRays[0].initPt[2];
        bool blocked = false;
        float cDistance;

        std::vector<Ray> sRays;
        glm::vec3 norm;

        for (auto object : objects)
        {
            sRays = object->intersect(shadowRays[0], *lightSource, cDistance, norm);
            if (sRays.size() >= 1)
            {
                blocked = true;
                std::cout << *object << std::endl;
            }
        }

        color[0] = (!blocked) * hitObject->albedo / M_PI * lightSource->intensity * std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255 * 4 * hitObject->color[0];
        color[1] = (!blocked) * hitObject->albedo / M_PI * lightSource->intensity * std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255 * 4 * hitObject->color[1];
        color[2] = (!blocked) * hitObject->albedo / M_PI * lightSource->intensity * std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255 * 4 * hitObject->color[2];
    }
    return color;
}

void Scene::render()
{
    auto lightSource = sources[0];
    cv::Mat image(cv::Size(camera->resX, camera->resY), CV_8UC3);

    cv::Vec3b color(0, 0, 0);
    for (unsigned x = 0; x < camera->resX; ++x)
    {
        //std::cout << x << std::endl;
        for (unsigned y = 0; y < camera->resY; ++y)
        {
            Ray primRay = camera->genRay(x, y);
            color = castRay(primRay, lightSource, objects);
            image.at<cv::Vec3b>(x, y) = color;
        };
    }
    cv::resize(image, image, cv::Size(1000, 1000));
    cv::imwrite("RayTracing.png", image);
    cv::imshow("RayTracing", image);
}

#include "Scene.hpp"
#include <algorithm>
#define MAX_DEPTH 1
#include <opencv2/opencv.hpp>

cv::Vec3b castRay(Ray const &ray, std::shared_ptr<LightSource> const &lightSource, std::vector<std::shared_ptr<ObjectBase>> const &objects, const int &depth = 0)
{
    cv::Vec3b color(0, 0, 0);
    if (depth > MAX_DEPTH)
        return color;
    else
    {
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
            shadowRays = hitObject->intersect(ray, *lightSource, distance, hitNormal);
            // Delete acne
            shadowRays[0].initPt[0] = hitNormal[0] * 0.0001 + shadowRays[0].initPt[0];
            shadowRays[0].initPt[1] = hitNormal[1] * 0.0001 + shadowRays[0].initPt[1];
            shadowRays[0].initPt[2] = hitNormal[2] * 0.0001 + shadowRays[0].initPt[2];

            bool blocked = false;
            float cDistance;

            std::vector<Ray> sRays;
            glm::vec3 norm;

            for (auto object : objects)
            {
                sRays = object->intersect(shadowRays[0], *lightSource, cDistance, norm);

                //Si le rayon est obstrué avant la source lumineuse
                if (sRays.size() and cDistance < glm::distance(lightSource->pos, shadowRays[0].initPt))
                {
                    /*std::cout << *object << std::endl;
                    std::cout << ray << std::endl
                              << shadowRays[0] << std::endl
                              << sRays[0] << std::endl 
                              << cDistance << " - " <<glm::distance(lightSource->pos, shadowRays[0].initPt)<<std::endl;*/
                    blocked = true;
                }
            }

            color[0] = (1 - hitObject->reflexionIndex) * (!blocked) * hitObject->albedo / M_PI * lightSource->intensity * std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255 * 4 * hitObject->color[0];
            color[1] = (1 - hitObject->reflexionIndex) * (!blocked) * hitObject->albedo / M_PI * lightSource->intensity * std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255 * 4 * hitObject->color[1];
            color[2] = (1 - hitObject->reflexionIndex) * (!blocked) * hitObject->albedo / M_PI * lightSource->intensity * std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 255 * 4 * hitObject->color[2];

            // If reflective
            if (hitObject->reflexionIndex)
            {
                //std::cout << "reflexion\n";

                Ray reflectedRay(shadowRays[0].initPt, shadowRays[0].dir - 2 * glm::dot(shadowRays[0].dir, hitNormal) * hitNormal);
                //std::cout << "\nInbound: " << shadowRays[0] << "\nOutbound: " << reflectedRay << std::endl;
                //if (shadowRays[0].dir[2] > -reflectedRay.dir[2] + 1e4 || shadowRays[0].dir[2] < -reflectedRay.dir[2] - 1e4)
                //    std::cout << "\nInbound: " << shadowRays[0].dir[2] << "\nOutbound: " << reflectedRay.dir[2] << std::endl;
                cv::Vec3b ref = castRay(reflectedRay, lightSource, objects, depth + 1);
                //std::cout << ref << std::endl;
                color[0] += hitObject->reflexionIndex * ref[0] * hitObject->color[0];
                color[1] += hitObject->reflexionIndex * ref[1] * hitObject->color[1];
                color[2] += hitObject->reflexionIndex * ref[2] * hitObject->color[2];
                //std::cout << color << std::endl;
            }
        }
        return color;
    }
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
            int depth = 0;
            Ray primRay = camera->genRay(x, y);
            color = castRay(primRay, lightSource, objects, depth);
            image.at<cv::Vec3b>(x, y) = color;
        };
    }
    cv::resize(image, image, cv::Size(1000, 1000));
    cv::imwrite("RayTracing.png", image);
    cv::imshow("RayTracing", image);
}

#include "Scene.hpp"
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <glm/gtc/constants.hpp>
#define MAX_DEPTH 30

cv::Vec3b castRay(Ray const &ray, std::shared_ptr<Light> const &lightSource, std::vector<std::shared_ptr<ObjectBase>> const &objects, const int &depth = 0)
{
    cv::Vec3b color(0, 0, 0);
    if (depth > MAX_DEPTH)
        return color;
    else
    {
        //std::cout << std::endl << std::endl;
        std::vector<Ray> shadowRays;
        glm::vec3 hitNormal;
        cv::Vec3b rColor;
        float closestDistance = INFINITY;
        float lDistance; //light distance
        float iDistance; //intersection distance
        std::shared_ptr<ObjectBase> hitObject = nullptr;
        for (auto object : objects)
        {
            shadowRays = object->intersect(ray, lightSource, iDistance, lDistance, hitNormal, rColor);
            //std::cout << iDistance << std::endl;
            if (shadowRays.size() && iDistance < closestDistance)
            {
                hitObject = object;
                closestDistance = iDistance;
            }
        }
        if (hitObject)
        {

            // Calcul des rayons de diffusion

            shadowRays = hitObject->intersect(ray, lightSource, iDistance, lDistance, hitNormal, rColor);
            //std::cout << ray << std::endl
            //          << shadowRays[0] << std::endl;
            // Delete acne
            //std::cout << hitNormal << std::endl;
            shadowRays[0].biais(hitNormal, 0.0001f);

            bool blocked = false;
            float iDistance; // distance with the intersection

            std::vector<Ray> sRays;
            glm::vec3 norm;

            cv::Vec3b _rColor; // unsaved
            for (auto object : objects)
            {
                sRays = object->intersect(shadowRays[0], lightSource, iDistance, lDistance, norm, _rColor);

                //Si le rayon est obstrué avant la source lumineuse
                if (sRays.size() and iDistance < lDistance)
                {
                    /*std::cout << *object << std::endl;
                    std::cout << ray << std::endl
                              << shadowRays[0] << std::endl
                              << sRays[0] << std::endl 
                              << cDistance << " - " <<glm::distance(lightSource->pos, shadowRays[0].initPt)<<std::endl;*/
                    blocked = true;
                }
            }
            cv::Vec3b ref1;
            cv::multiply(rColor, hitObject->color, ref1);
            color = ref1 * (1 - hitObject->reflexionIndex) * (!blocked) * hitObject->albedo * 255 / glm::pi<float>() * std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir)) * 2;

            // Calcul des rayons de diffusion
            //std::cout << *hitObject/*->reflexionIndex*/ << std::endl;
            if (hitObject->reflexionIndex)
            {
                //std::cout << "reflexion\n";

                Ray reflectedRay(shadowRays[0].initPt, ray.dir - 2 * glm::dot(ray.dir, hitNormal) * hitNormal);
                //std::cout << "\nInbound: " << ray << std::endl
                //          << hitNormal << "\nOutbound: " << reflectedRay << std::endl;
                //if (shadowRays[0].dir[2] > -reflectedRay.dir[2] + 1e4 || shadowRays[0].dir[2] < -reflectedRay.dir[2] - 1e4)
                //    std::cout << "\nInbound: " << shadowRays[0].dir[2] << "\nOutbound: " << reflectedRay.dir[2] << std::endl;
                cv::Vec3b ref;
                cv::multiply(hitObject->color, castRay(reflectedRay, lightSource, objects, depth + 1), ref);
                //std::cout << ref << std::endl;
                color += hitObject->reflexionIndex * ref;
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
            //std::cout << y << std::endl;
            //unsigned x = 500;unsigned y=400;
            int depth = 0;
            Ray primRay = camera->genRay(x, y);
            //std::cout << primRay << std::endl;
            color = castRay(primRay, lightSource, objects, depth);
            image.at<cv::Vec3b>(x, y) = color;
        };
    }
    cv::resize(image, image, cv::Size(1000, 1000));
    cv::imwrite("RayTracing.png", image);
    cv::imshow("RayTracing", image);
}

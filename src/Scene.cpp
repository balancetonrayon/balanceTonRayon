#include "Scene.hpp"

#include <algorithm>

#include <glm/gtc/constants.hpp>
#include <opencv2/opencv.hpp>

#define MAX_DEPTH 50

/* Fresnel function as explained here :
https://www.scratchapixel.com/lessons/3d-basic-rendering/introduction-to-shading/reflection-refraction-fresnel
ior is the refraction index of the material of the physical object the ray has either hit or is
about to leave (glass, water, etc.) */
float fresnel(const Ray &iRay, const glm::vec3 &normal, const float &refractionIndex) {
    float kr;  // quantity of reflexion to be computed

    float cosi = std::clamp(glm::dot(iRay.dir, normal), -1.0f, 1.0f);
    float etai = 1;                // air
    float etat = refractionIndex;  // medium
    if (cosi > 0) {
        std::swap(etai, etat);
    }
    // Compute sini using Snell's law
    float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
    // Total internal reflection
    if (sint >= 1) {
        kr = 1;
    } else {
        float cost = sqrtf(std::max(0.f, 1 - sint * sint));
        cosi = fabsf(cosi);
        float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
        float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
        kr = (Rs * Rs + Rp * Rp) / 2;
    }

    return kr;
    // As a consequence of the conservation of energy, transmittance is given by:
    // kt = 1 - kr;
}

/* A EXPLIQUER et comprendre */
glm::vec3 refract(const Ray &iRay, const glm::vec3 &normal, const float &refractionIndex) {
    float cosi = std::clamp(glm::dot(iRay.dir, normal), -1.0f, 1.0f);
    float etai = 1;                // air
    float etat = refractionIndex;  // medium
    glm::vec3 n = normal;
    if (cosi < 0) {
        // outside the surface, so we want cos(theta) to be positive
        cosi = -cosi;
    } else {
        // inside: oppose the normal and swap the indices
        std::swap(etai, etat);
        n = -normal;
    }
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    // if k < 0: total internal reflection
    return k < 0 ? glm::vec3() : iRay.dir * eta + n * (eta * cosi - sqrtf(k));
}

glm::vec3 castRay(Ray const &ray, std::shared_ptr<Light> const &lightSource,
                  std::vector<std::shared_ptr<ObjectBase>> const &objects, const int &depth = 0) {
    glm::vec3 color(0, 0, 0);
    if (depth > MAX_DEPTH) {
        return color;
    } else {
        // std::cout << std::endl << std::endl;
        std::vector<Ray> shadowRays;
        glm::vec3 hitNormal;
        glm::vec3 rColor;
        float closestDistance = INFINITY;
        float lDistance;  // light distance
        float iDistance;  // intersection distance
        std::shared_ptr<ObjectBase> hitObject = nullptr;
        for (auto object : objects) {
            shadowRays =
                object->intersect(ray, lightSource, iDistance, lDistance, hitNormal, rColor);
            // std::cout << iDistance << std::endl;
            if (shadowRays.size() && iDistance < closestDistance) {
                hitObject = object;
                closestDistance = iDistance;
            }
        }
        if (hitObject) {
            // Calcul des rayons de diffusion

            shadowRays =
                hitObject->intersect(ray, lightSource, iDistance, lDistance, hitNormal, rColor);
            // std::cout << ray << std::endl
            //          << shadowRays[0] << std::endl;

            // Delete acne
            // std::cout << hitNormal << std::endl;
            shadowRays[0].biais(hitNormal, 0.0001f);

            bool blocked = false;
            float iDistance;  // distance with the intersection

            std::vector<Ray> sRays;
            glm::vec3 norm;

            glm::vec3 _rColor;  // unsaved
            for (auto object : objects) {
                sRays = object->intersect(shadowRays[0], lightSource, iDistance, lDistance, norm,
                                          _rColor);

                // Si le rayon est obstrué avant la source lumineuse
                if (sRays.size() && iDistance < lDistance) {
                    /*std::cout << *object << std::endl;
                    std::cout << ray << std::endl
                              << shadowRays[0] << std::endl
                              << sRays[0] << std::endl
                              << cDistance << " - "
                    <<glm::distance(lightSource->pos,
                    shadowRays[0].initPt)<<std::endl;*/
                    blocked = true;
                }
            }
            color = detail::mult(rColor, hitObject->color) * (1 - hitObject->reflexionIndex) *
                    (float)(!blocked) * hitObject->albedo / glm::pi<float>() *
                    std::max(0.f, glm::dot(hitNormal, shadowRays[0].dir));

            // std::cout << *hitObject/*->reflexionIndex*/ << std::endl;
            if (hitObject->reflexionIndex && !hitObject->transparency) {
                // std::cout << "reflexion\n";

                Ray reflectedRay(shadowRays[0].initPt,
                                 ray.dir - 2 * glm::dot(ray.dir, hitNormal) * hitNormal);
                // std::cout << "\nInbound: " << ray << std::endl
                //          << hitNormal << "\nOutbound: " << reflectedRay <<
                //          std::endl;
                // if (shadowRays[0].dir[2] > -reflectedRay.dir[2] + 1e4 ||
                // shadowRays[0].dir[2] < -reflectedRay.dir[2] - 1e4)
                //    std::cout << "\nInbound: " << shadowRays[0].dir[2] <<
                //    "\nOutbound: " << reflectedRay.dir[2] << std::endl;

                // std::cout << ref << std::endl;
                color += detail::mult(hitObject->color,
                                      castRay(reflectedRay, lightSource, objects, depth + 1)) *
                         hitObject->reflexionIndex;
                // std::cout << color << std::endl;
            }

            if (hitObject->transparency) {
                glm::vec3 refractionColor;
                // compute fresnel
                float kr = fresnel(ray, hitNormal, hitObject->refractiveIndex);
                bool outside = glm::dot(ray.dir, hitNormal) < 0;
                // compute refraction if it is not a case of total internal reflection
                if (kr < 1) {
                    Ray refractedRay = Ray(shadowRays[0].initPt,
                                           refract(ray, hitNormal, hitObject->refractiveIndex));
                    outside ? refractedRay.biais(-hitNormal, 0.001f)
                            : refractedRay.biais(+hitNormal, 0.001f);
                    refractionColor = castRay(refractedRay, lightSource, objects, depth + 1);
                }

                Ray reflectedRay = Ray(shadowRays[0].initPt,
                                       ray.dir - 2 * glm::dot(ray.dir, hitNormal) * hitNormal);
                outside ? reflectedRay.biais(+hitNormal, 0.001f)
                        : reflectedRay.biais(-hitNormal, 0.001f);
                glm::vec3 reflectionColor = castRay(reflectedRay, lightSource, objects, depth + 1);

                // mix the two
                color +=
                    reflectionColor * kr + refractionColor * (1 - kr) * hitObject->transparency;
            }
        }
        if (color[0] > 255 || color[1] > 255 || color[2] > 255)
            std::cout << "Color overflow ! " << color << std::endl;
        return color;
    }
}

void Scene::render() {
    auto lightSource = sources[0];
    cv::Mat image(cv::Size(camera->resX, camera->resY), CV_8UC3);

    cv::Vec3b color(0, 0, 0);
    for (unsigned x = 0; x < camera->resX; ++x) {
        // std::cout << x << std::endl;u
        for (unsigned y = 0; y < camera->resY; ++y) {
            // std::cout << y << std::endl;
            // unsigned x = 500;unsigned y=400;
            int depth = 0;
            Ray primRay = camera->genRay(x, y);
            // std::cout << primRay << std::endl;
            color = detail::glm2cv(castRay(primRay, lightSource, objects, depth));
            image.at<cv::Vec3b>(x, y) = color;
        }
    }
    cv::resize(image, image, cv::Size(1000, 1000));
    cv::imwrite("RayTracing.png", image);
    cv::imshow("RayTracing", image);
}

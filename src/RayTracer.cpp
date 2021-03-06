/**
 * @file RayTracer.cpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief The main part of the project. The ray tracing algorithms in themselves
 * @version 1.0
 *
 * @copyright The fresnel and refract functions have been refactored from scratchapixels code. The
 * other functions have been written entirely by the authors with the ideas of scratchapixel and
 * other websites.
 *
 */
#include "RayTracer.hpp"

#include <algorithm>

#include <glm/gtc/constants.hpp>

float fresnel(Ray iRay, const glm::vec3 &normal, const float &refractionIndex) {
    float kr;  // quantity of reflexion to be computed

    float cosi = std::clamp(glm::dot(iRay.getDir(), normal), -1.0f, 1.0f);
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

glm::vec3 refract(const Ray &iRay, const glm::vec3 &normal, const float &refractionIndex) {
    float cosi = std::clamp(glm::dot(iRay.getDir(), normal), -1.0f, 1.0f);
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
    return k < 0 ? glm::vec3() : iRay.getDir() * eta + n * (eta * cosi - sqrtf(k));
}

glm::vec3 castRay(Ray const &ray, std::shared_ptr<Light> const &lightSource,
                  std::vector<std::shared_ptr<BasicObject>> const &objects,
                  const glm::vec3 &backgroundColor, const int &depth, const int &maxDepth) {
    glm::vec3 color = backgroundColor;
    if (depth > maxDepth) {
        return color;
    } else {
        // std::cout << std::endl << std::endl;
        std::vector<Ray> shadowRays;
        Inter inter;
        float closestDistance = INFINITY;

        std::shared_ptr<BasicObject> hitObject = nullptr;

        for (auto object : objects) {
            shadowRays = object->intersect(ray, lightSource, inter);
            // std::cout << iDistance << std::endl;
            if (shadowRays.size() && inter.id < closestDistance) {
                hitObject = object;
                closestDistance = inter.id;
            }
        }
        if (hitObject) {
            // Calcul des rayons de diffusion

            shadowRays = hitObject->intersect(ray, lightSource, inter);
            // std::cout << ray << std::endl << shadowRays[0] << std::endl;

            // Delete acne
            // std::cout << hitNormal << std::endl;
            shadowRays[0].biais(inter.normal, 0.0001f);

            bool blocked = false;
            float iDistance;  // distance with the intersection

            std::vector<Ray> sRays;
            glm::vec3 norm;

            Inter blockedInter;
            for (auto object : objects) {
                sRays = object->intersect(shadowRays[0], lightSource, blockedInter);

                // Si le rayon est obstrué avant la source lumineuse
                if (sRays.size() && blockedInter.id < blockedInter.ld) {
                    /*std::cout << *object << std::endl;
                    std::cout << ray << std::endl
                              << shadowRays[0] << std::endl
                              << sRays[0] << std::endl
                              << " - " << glm::distance(lightSource->pos, shadowRays[0].getInitPt())
                              << " " << blockedInter.id << " " << blockedInter.ld << " "
                              << blockedInter.normal << std::endl;*/
                    blocked = true;
                }
            }
            color = detail::mult(inter.rColor, inter.objColor) * (1 - inter.objReflexionIndex) *
                    (float)(!blocked) * inter.objAlbedo / glm::pi<float>() *
                    std::max(0.f, glm::dot(inter.normal, shadowRays[0].getDir()));
            /*std::cout << *hitObject << hitObject->reflexionIndex<< std::endl;
            std::cout << inter.rColor << " " << hitObject->color << " " << (float)(!blocked) << " "
                      << hitObject->albedo << " " << (1 - hitObject->reflexionIndex) << " "
                      << std::max(0.f, glm::dot(inter.normal, shadowRays[0].dir)) << " " << color
                      << std::endl;*/
            // std::cout << *hitObject/*->reflexionIndex*/ << std::endl;
            if (inter.objReflexionIndex && !inter.objTransparency) {
                // std::cout << "reflexion\n";

                Ray reflectedRay(
                    shadowRays[0].getInitPt(),
                    ray.getDir() - 2 * glm::dot(ray.getDir(), inter.normal) * inter.normal);
                // std::cout << "\nInbound: " << ray << std::endl
                //          << hitNormal << "\nOutbound: " << reflectedRay <<
                //          std::endl;
                // if (shadowRays[0].dir[2] > -reflectedRay.dir[2] + 1e4 ||
                // shadowRays[0].dir[2] < -reflectedRay.dir[2] - 1e4)
                //    std::cout << "\nInbound: " << shadowRays[0].dir[2] <<
                //    "\nOutbound: " << reflectedRay.dir[2] << std::endl;

                // std::cout << ref << std::endl;
                color +=
                    detail::mult(hitObject->color, castRay(reflectedRay, lightSource, objects,
                                                           backgroundColor, depth + 1, maxDepth)) *
                    hitObject->reflexionIndex;
                // std::cout << color << std::endl;
            }

            if (inter.objTransparency) {
                glm::vec3 refractionColor;
                // compute fresnel
                float kr = fresnel(ray, inter.normal, hitObject->refractiveIndex);
                bool outside = glm::dot(ray.getDir(), inter.normal) < 0;
                // compute refraction if it is not a case of total internal reflection
                if (kr < 1) {
                    Ray refractedRay = Ray(shadowRays[0].getInitPt(),
                                           refract(ray, inter.normal, hitObject->refractiveIndex));
                    outside ? refractedRay.biais(-inter.normal, 0.001f)
                            : refractedRay.biais(+inter.normal, 0.001f);
                    refractionColor = castRay(refractedRay, lightSource, objects, backgroundColor,
                                              depth + 1, maxDepth);
                }

                Ray reflectedRay =
                    Ray(shadowRays[0].getInitPt(),
                        ray.getDir() - 2 * glm::dot(ray.getDir(), inter.normal) * inter.normal);
                outside ? reflectedRay.biais(+inter.normal, 0.001f)
                        : reflectedRay.biais(-inter.normal, 0.001f);
                glm::vec3 reflectionColor = castRay(reflectedRay, lightSource, objects,
                                                    backgroundColor, depth + 1, maxDepth);

                // mix the two
                color +=
                    reflectionColor * kr + refractionColor * (1 - kr) * hitObject->transparency;
            }
        } else {  // If no intersection, set the color to the background color
            color = backgroundColor;
        }
        if (color[0] > 255 || color[1] > 255 || color[2] > 255)
            std::cout << "Color overflow ! " << color << std::endl;
        return color;
    }
}

void StdRayTracer::render(const Scene &scene, std::string filename) const {
    ImgHandler imgHandler;

    auto lightSources = scene.getSources()[0];
    auto objects = scene.getObjects();
    auto camera = scene.getCamera();

    std::vector<unsigned char> image;
    glm::vec3 color;

    for (unsigned x = 0; x < camera->resX; ++x) {
        for (unsigned y = 0; y < camera->resY; ++y) {
            int depth = 0;
            Ray primRay = camera->genRay(x, y);

            color = castRay(primRay, lightSources, objects, scene.getColor(), depth,
                            this->getMaxDepth());
            std::vector<unsigned char> colorVec{(unsigned char)color[0], (unsigned char)color[1],
                                                (unsigned char)color[2], (unsigned char)255};
            image.insert(image.end(), colorVec.begin(), colorVec.end());
        }
    }
    if (this->getAdaptation()) adaptLuminosity(image);
    imgHandler.writePNG(filename, image, camera->resX, camera->resY);
}

void FixedAntiAliasingRayTracer::render(const Scene &scene, std::string filename) const {
    ImgHandler imgHandler;

    int sqrtAAPower = this->getAAPower();
    float d = 1.0 / sqrtAAPower;

    auto lightSources = scene.getSources()[0];
    auto objects = scene.getObjects();
    auto camera = scene.getCamera();

    std::vector<unsigned char> image;

    glm::vec3 color;
    for (float x = 0; x < camera->resX; ++x) {
        for (float y = 0; y < camera->resY; ++y) {
            color = glm::vec3(0, 0, 0);

            for (int idRayV = 1; idRayV < sqrtAAPower + 1; ++idRayV) {
                for (int idRayH = 1; idRayH < sqrtAAPower + 1; ++idRayH) {
                    int depth = 0;
                    Ray primRay = camera->genRay(x + d * idRayH, y + d * idRayV);
                    color = color + castRay(primRay, lightSources, objects, scene.getColor(), depth,
                                            this->getMaxDepth());
                }
            }
            color = color / ((float)(sqrtAAPower * sqrtAAPower));
            std::vector<unsigned char> colorVec{(unsigned char)color[0], (unsigned char)color[1],
                                                (unsigned char)color[2], (unsigned char)255};
            image.insert(image.end(), colorVec.begin(), colorVec.end());
        }
    }
    if (this->getAdaptation()) adaptLuminosity(image);
    imgHandler.writePNG(filename, image, camera->resX, camera->resY);
}

// A finir :( 
/*void StochasticAntiAliasingRayTracer::render(Scene scene, std::string filename) {
    int sqrtAAPower = this->getAAPower();
    float d = 1.0 / sqrtAAPower;

    auto lightSources = scene.getSources()[0];
    auto objects = scene.getObjects();
    auto camera = scene.getCamera();

    cv::Mat image(cv::Size(camera->resX, camera->resY), CV_8UC3);

    glm::vec3 color;
    for (float x = 0; x < camera->resX; ++x) {
        std::cout << x << std::endl;
        for (float y = 0; y < camera->resY; ++y) {
            color = glm::vec3(0, 0, 0);
            glm::vec3 tmp = glm::vec3(0, 0, 0);
            for (int idRayV = 1; idRayV < sqrtAAPower + 1; ++idRayV) {
                for (int idRayH = 1; idRayH < sqrtAAPower + 1; ++idRayH) {
                    int depth = 0;
                    Ray primRay = camera->genRay(x + d * idRayH, y + d * idRayV);
                    tmp = castRay(primRay, lightSources, objects, scene.getColor(), depth);
                    color = color + tmp;
                    //std::cout << d << " " << x + d * (float)idRayH << primRay << " " << tmp << "
";
                }
            }

            image.at<cv::Vec3b>(x, y) =
                detail::glm2cv(color / ((float)(sqrtAAPower * sqrtAAPower)));
            //std::cout << detail::glm2cv(color / ((float)(sqrtAAPower * sqrtAAPower))) <<
std::endl;
        }
    }
    cv::resize(image, image, cv::Size(1000, 1000));
    cv::imwrite("RayTracing.png", image);
    cv::imshow("RayTracing", image);
}*/
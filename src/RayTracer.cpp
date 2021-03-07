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
#include <chrono>

#include <glm/gtc/constants.hpp>
#include <omp.h>

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
    glm::vec3 color = backgroundColor * 255.0f;
    if (depth > maxDepth) {
        return color;
    } else {
        std::vector<Ray> shadowRays;
        Inter inter;
        float closestDistance = INFINITY;

        std::shared_ptr<BasicObject> hitObject = nullptr;

        for (auto object : objects) {
            object->intersect(ray, lightSource, inter, shadowRays);

            if (shadowRays.size() && inter.id < closestDistance) {
                hitObject = object;
                closestDistance = inter.id;
            }
            shadowRays.clear();
        }
        if (hitObject) {
            // Calcul des rayons de diffusion
            shadowRays.clear();
            hitObject->intersect(ray, lightSource, inter, shadowRays);

            shadowRays[0].biais(inter.normal, 0.00001f);

            bool blocked = false;

            std::vector<Ray> sRays;
            glm::vec3 norm;

            Inter blockedInter;
            for (auto object : objects) {
                object->intersect(shadowRays[0], lightSource, blockedInter, sRays);

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
                sRays.clear();
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
                Ray reflectedRay(
                    shadowRays[0].getInitPt(),
                    ray.getDir() - 2 * glm::dot(ray.getDir(), inter.normal) * inter.normal);

                color +=
                    detail::mult(hitObject->color, castRay(reflectedRay, lightSource, objects,
                                                           backgroundColor, depth + 1, maxDepth)) *
                    hitObject->reflexionIndex;
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
                outside ? reflectedRay.biais(+inter.normal, 0.00001f)
                        : reflectedRay.biais(-inter.normal, 0.00001f);
                glm::vec3 reflectionColor = castRay(reflectedRay, lightSource, objects,
                                                    backgroundColor, depth + 1, maxDepth);

                // mix the two
                color +=
                    reflectionColor * kr + refractionColor * (1 - kr) * hitObject->transparency;
            }
        } else {  // If no intersection, set the color to the background color
            color = backgroundColor * 255.0f;
        }

        return color;
    }
}

void StdRayTracer::render(const Scene &scene, const std::string &filename) const {
    std::chrono::time_point<std::chrono::system_clock> start, end, startRT, endRT, startC, endC;
    std::chrono::duration<double> elapsRT;
    double duration = 0;
    ImgHandler imgHandler;

    auto lightSources = scene.getSources()[0];
    auto objects = scene.getObjects();
    auto camera = scene.getCamera();

    int resX = camera->resX;
    int resY = camera->resY;

    std::vector<unsigned char> image(scene.getCamera()->getNumberOfPixels() * 4);
    glm::vec3 backgroundColor = scene.getBackgroundColor();
    start = std::chrono::system_clock::now();

#pragma omp parallel for simd schedule(dynamic, 10)
    for (unsigned x = 0; x < camera->resX; ++x) {
        for (unsigned y = 0; y < camera->resY; ++y) {
            int depth = 0;

            Ray primRay = camera->genRay(x, y);

            if (omp_get_thread_num() == 0) startRT = std::chrono::system_clock::now();
            glm::vec3 color = castRay(primRay, lightSources, objects, backgroundColor, depth,
                                      this->getMaxDepth());
            if (omp_get_thread_num() == 0) {
                endRT = std::chrono::system_clock::now();
                elapsRT = endRT - startRT;
                duration += elapsRT.count();
            }

            image[((int)x * resX + (int)y) * 4] = (unsigned char)color[0];
            image[((int)x * resX + (int)y) * 4 + 1] = (unsigned char)color[1];
            image[((int)x * resX + (int)y) * 4 + 2] = (unsigned char)color[2];
            image[((int)x * resX + (int)y) * 4 + 3] = (unsigned char)255;
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elaps = end - start;
    std::cout << "CPU(s) : calcul " << elaps.count() << std::endl
              << "RT: " << duration << std::endl;

    imgHandler.writePNG(filename, image, camera->resX, camera->resY);
}

void FixedAntiAliasingRayTracer::render(const Scene &scene, const std::string &filename) const {
    std::chrono::time_point<std::chrono::system_clock> start, end, startRT, endRT;
    std::chrono::duration<double> elapsRT;
    double duration = 0;

    ImgHandler imgHandler;

    std::vector<unsigned char> image(scene.getCamera()->getNumberOfPixels() * 4);
    start = std::chrono::system_clock::now();

    int sqrtAAPower = this->getAAPower();
    float d = 1.0 / sqrtAAPower;

    auto lightSources = scene.getSources()[0];
    auto objects = scene.getObjects();
    auto camera = scene.getCamera();
    int resX = camera->resX;
    int resY = camera->resY;
    int maxDepth = this->getMaxDepth();

    glm::vec3 backgroundColor = scene.getBackgroundColor();

#pragma omp parallel for simd schedule(dynamic, 10)
    for (int x = 0; x < resX; x++) {
        // std::cout << x << std::endl;
        // std::cout << omp_get_thread_num() << std::endl;
        for (int y = 0; y < resY; y++) {
            glm::vec3 color = glm::vec3(0, 0, 0);

            for (int idRayV = 1; idRayV < sqrtAAPower + 1; ++idRayV) {
                for (int idRayH = 1; idRayH < sqrtAAPower + 1; ++idRayH) {
                    int depth = 0;
                    Ray primRay = camera->genRay((float)x + d * idRayH, (float)y + d * idRayV);
                    if (omp_get_thread_num() == 0) startRT = std::chrono::system_clock::now();
                    color = color + castRay(primRay, lightSources, objects, backgroundColor, depth,
                                            maxDepth);
                    if (omp_get_thread_num() == 0) {
                        endRT = std::chrono::system_clock::now();
                        elapsRT = endRT - startRT;
                        duration += elapsRT.count();
                    }
                }
            }
            color = color / ((float)(sqrtAAPower * sqrtAAPower));
            image[((int)x * resX + (int)y) * 4] = (unsigned char)color[0];
            image[((int)x * resX + (int)y) * 4 + 1] = (unsigned char)color[1];
            image[((int)x * resX + (int)y) * 4 + 2] = (unsigned char)color[2];
            image[((int)x * resX + (int)y) * 4 + 3] = (unsigned char)255;
        }
    }

    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elaps = end - start;
    std::cout << "CPU(s) : calcul " << elaps.count() << std::endl
              << "RT: " << duration << std::endl;

    imgHandler.writePNG(filename, image, scene.getCamera()->resX, scene.getCamera()->resY);
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
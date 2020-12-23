#include "Object.hpp"

#include <cmath>
#include <memory>

#include <glm/gtc/constants.hpp>

#include "utils.hpp"

std::ostream &Light::printInfo(std::ostream &os) const {
    return os << "Light: in " << pos << ", of color: " << color;
}

std::vector<Ray> DirectLight::outboundRays(glm::vec3 hitPt) const {
    std::vector<Ray> rays;
    Ray ray;
    ray.initPt = hitPt;
    ray.dir = glm::normalize(pos - hitPt);
    ray.color = color * intensity;
    rays.push_back(ray);
    return rays;
}

std::vector<Ray> SpotLight::outboundRays(const glm::vec3 hitPt) const {
    std::vector<Ray> rays;
    Ray ray;
    ray.initPt = hitPt;
    ray.dir = glm::normalize(pos - hitPt);
    ray.color =
        color * static_cast<float>(intensity / (4 * glm::pi<float>() *
glm::dot(pos - hitPt, pos - hitPt)));
    rays.push_back(ray);                                       
    return rays;
}

std::vector<Ray> AreaLight::outboundRays(const glm::vec3 hitPt) const {
    std::vector<Ray> rays;
    Ray ray;
    ray.initPt = hitPt;
    ray.dir = glm::normalize(pos - hitPt);
    ray.color =
        color *
        std::min(255.0f, static_cast<float>(intensity / (4 * glm::pi<float>() *
                                                         glm::dot(pos - hitPt, pos - hitPt))));
    rays.push_back(ray);                                       
    return rays;
}

Ray Camera::genRay(unsigned x, unsigned y) noexcept {
    try {
        if (x>resX || y>resY || x<0 || y<0) throw Camera::pixel_out_of_range();
    }
    catch (Camera::pixel_out_of_range exception) {
        std::cout << "Pixel out of range" << std::endl; 
    }

    glm::vec3 rDir = dir * focalLength + hv * (float)((float)y / resY - 0.5) * sizeY + 
                  vv * (float)((float)x / resX - 0.5) * sizeX;

    //std::cout << Ray(pos, dir) << std::endl;
    return Ray(pos, rDir);
}

std::ostream &Camera::printInfo(std::ostream &os) const {
    return os << "Camera: in " << pos << ", of size: " << sizeX;
}

std::vector<Ray> Plane::intersect(const Ray iRay, const std::shared_ptr<Light> ltSrc,
                                  float &iDistance, float &lDistance, glm::vec3 &hitNormal,
                                  glm::vec3 &rColor) const {
    std::vector<Ray> rays;
    /*if (glm::dot(iRay.dir, normal) > 0)
        normal = -normal;*/

    bool inter = glm::intersectRayPlane(iRay.initPt, iRay.dir, pos, normal, iDistance);
    if (inter) {
        glm::vec3 intersectPt = iRay.initPt + iDistance * iRay.dir;
        hitNormal = normal;

        Ray oRay = ltSrc->outboundRays(intersectPt)[0];

        //lDistance sho
        lDistance = glm::distance(intersectPt, ltSrc->pos);
        rColor = oRay.color;
        /*std::vector<Ray> rays;
        std::cout << ray << std::endl
                  << *this << std::endl
                  << intersectPt << std::endl
                  << distance
                  << std::endl
                  << std::endl;*/
        rays.push_back(oRay);
    }
    return rays;
}

std::ostream &Plane::printInfo(std::ostream &os) const {
    return os << "Plan: " << std::endl
              << "at: " << pos << std::endl
              << "normal: " << normal << std::endl
              << "albedo: " << albedo << std::endl
              << "reflexion: " << reflexionIndex;
}

std::vector<Ray> Sphere::intersect(const Ray iRay, const std::shared_ptr<Light> ltSrc,
                                   float &iDistance, float &lDistance, glm::vec3 &hitNormal,
                                glm::vec3 &rColor) const {
    std::vector<Ray> rays;

    glm::vec3 intersectPt;
    bool inter =
        glm::intersectRaySphere(iRay.initPt, iRay.dir, pos, radius, intersectPt, hitNormal);
    if (inter) {
        iDistance = glm::distance(iRay.initPt, intersectPt);
        // std::cout << "sphere distance: " << iDistance;
        Ray oRay = ltSrc->outboundRays(intersectPt)[0];
        lDistance = glm::distance(intersectPt, ltSrc->pos);
        rColor = oRay.color;
        /*std::vector<Ray> rays;
        std::cout << ray << std::endl
                  << *this << std::endl
                  << intersectPt << std::endl
                  << distance
                  << std::endl
                  << std::endl;*/
        rays.push_back(oRay);
    }
    return rays;
}

std::ostream &Sphere::printInfo(std::ostream &os) const {
    return os << "Sphere: " << std::endl
              << "at: " << pos << std::endl
              << "radius: " << radius << std::endl
              << "albedo: " << albedo;
}

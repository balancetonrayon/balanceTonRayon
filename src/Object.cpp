#include "Object.hpp"

#include <memory>

#include <glm/gtc/constants.hpp>

#include "utils.hpp"

std::ostream &Light::printInfo(std::ostream &os) const {
    return os << "Light: in " << pos << ", of color: " << color;
}

Ray DirectLight::outboundRay(glm::vec3 hitPt) const {
    Ray ray;
    ray.initPt = hitPt;
    ray.dir = glm::normalize(pos - hitPt);
    ray.color = color * intensity;
    return ray;
}

Ray SpotLight::outboundRay(const glm::vec3 hitPt) const {
    Ray ray;
    ray.initPt = hitPt;
    ray.dir = glm::normalize(pos - hitPt);
    ray.color =
        color *
        std::min(255.0f, static_cast<float>(intensity / (4 * glm::pi<float>() *
                                                         glm::dot(pos - hitPt, pos - hitPt))));
    return ray;
}

Ray Camera::genRay(unsigned x, unsigned y) {
    // EXCEPTION A AJOUTER
    // Z is the altitude : - X of the image
    glm::vec3 dir(focalLength, (-0.5 + static_cast<float>(y) / resY) * sizeY,
                  (0.5 - static_cast<float>(x) / resX) * sizeX);
    return Ray(pos, dir);
}

std::ostream &Camera::printInfo(std::ostream &os) const {
    return os << "Camera: in " << pos << ", of size: " << sizeX;
}

std::vector<Ray> Plane::intersect(const Ray iRay, const std::shared_ptr<Light> ltSrc,
                                  float &iDistance, float &lDistance, glm::vec3 &hitNormal,
                                  cv::Vec3b &rColor) const {
    std::vector<Ray> rays;
    /*if (glm::dot(iRay.dir, normal) > 0)
        normal = -normal;*/

    bool inter = glm::intersectRayPlane(iRay.initPt, iRay.dir, pos, normal, iDistance);
    if (inter) {
        glm::vec3 intersectPt = iRay.initPt + iDistance * iRay.dir;
        hitNormal = normal;
        Ray oRay = ltSrc->outboundRay(intersectPt);
        lDistance = glm::distance(intersectPt, ltSrc->pos);
        rColor = detail::glm2cv(oRay.color);
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
                                   cv::Vec3b &rColor) const {
    std::vector<Ray> rays;

    glm::vec3 intersectPt;
    bool inter =
        glm::intersectRaySphere(iRay.initPt, iRay.dir, pos, radius, intersectPt, hitNormal);
    if (inter) {
        iDistance = glm::distance(iRay.initPt, intersectPt);
        // std::cout << "sphere distance: " << iDistance;
        Ray oRay = ltSrc->outboundRay(intersectPt);
        lDistance = glm::distance(intersectPt, ltSrc->pos);
        rColor = detail::glm2cv(oRay.color);
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

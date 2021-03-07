#include "DirectLight.hpp"

void DirectLight::outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const {
    Ray ray;
    ray.setInitPt(hitPt);
    ray.setDir(glm::normalize(pos - hitPt));
    ray.setColor(color * intensity);
    rays.push_back(ray);
}

#include "SpotLight.hpp"

void SpotLight::outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const {
    Ray ray;
    ray.setInitPt(hitPt);
    ray.setDir(glm::normalize(pos - hitPt));
    ray.setColor(color * static_cast<float>(intensity / (4 * glm::pi<float>() *
                                                         glm::dot(pos - hitPt, pos - hitPt))));
    rays.push_back(ray);
}

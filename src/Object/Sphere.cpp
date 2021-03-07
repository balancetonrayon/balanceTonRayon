#include "Sphere.hpp"

void Sphere::intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                       std::vector<Ray> &rays) const {
    glm::vec3 intersectPt;
    bool intersect = glm::intersectRaySphere(iRay.getInitPt(), iRay.getDir(), pos, radius,
                                             intersectPt, inter.normal);
    if (intersect) {
        inter.id = glm::distance(iRay.getInitPt(), intersectPt);

        ltSrc->outboundRays(intersectPt, rays);
        inter.ld = glm::distance(intersectPt, ltSrc->pos);
        inter.rColor = rays[0].getColor();

        inter.objReflexionIndex = this->reflexionIndex;
        inter.objAlbedo = this->albedo;

        if (!definedTexture()) {
            inter.objColor = this->color;
            inter.objTransparency = this->transparency;
        } else {
            bool onTexture = false;
            glm::vec4 tmp = this->getTexture()->getColor(intersectPt, onTexture);
            if (onTexture) {
                inter.objColor = glm::vec3(tmp[0], tmp[1], tmp[2]);
                inter.objTransparency = tmp[3];
            } else {
                inter.objColor = this->color;
                inter.objTransparency = this->transparency;
            }
        }
    }
}

std::ostream &Sphere::printInfo(std::ostream &os) const {
    return os << "  - Sphere -" << std::endl
              << "at: " << pos << std::endl
              << "radius: " << radius << std::endl
              << "albedo: " << albedo;
}


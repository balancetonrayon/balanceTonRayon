#include "Plane.hpp"

void Plane::intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                      std::vector<Ray> &rays) const {
    // true if there is an intersection, false if there is none
    bool intersect = glm::intersectRayPlane(iRay.getInitPt(), iRay.getDir(), pos, normal, inter.id);
    if (intersect) {
        glm::vec3 intersectPt = iRay.getInitPt() + inter.id * iRay.getDir();
        inter.normal = normal;

        ltSrc->outboundRays(intersectPt, rays);

        inter.ld = glm::distance(intersectPt, ltSrc->pos);
        inter.rColor = rays[0].getColor();

        inter.objAlbedo = this->albedo;
        inter.objReflexionIndex = this->reflexionIndex;

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

std::ostream &Plane::printInfo(std::ostream &os) const {
    return os << "   - Plan -" << std::endl
              << "at: " << pos << std::endl
              << "normal: " << normal << std::endl
              << "albedo: " << albedo << std::endl
              << "reflexion: " << reflexionIndex;
}

#include "Triangle.hpp"

void Triangle::intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                         std::vector<Ray> &rays) const {
    // Intersect or not ? Moller Trumbore algorithm (from scratchapixels)
    glm::vec3 v0v1 = pos1 - pos;
    glm::vec3 v0v2 = pos2 - pos;
    glm::vec3 pvec = glm::cross(iRay.getDir(), v0v2);
    float det = glm::dot(v0v1, pvec);

    // ray and triangle are parallel if det is close to 0
    if (fabs(det) < KEPSILON) return;
    float invDet = 1 / det;

    glm::vec3 tvec = iRay.getInitPt() - pos;
    float u = glm::dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) return;

    glm::vec3 qvec = glm::cross(tvec, v0v1);
    float v = glm::dot(iRay.getDir(), qvec) * invDet;
    if (v < 0 || u + v > 1) return;

    // distance to intersection
    float t = glm::dot(v0v2, qvec) * invDet;
    if (t < 0) return;

    inter.id = t;
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

std::ostream &Triangle::printInfo(std::ostream &os) const {
    return os << "  - Triangle -" << std::endl
              << "v0: " << pos << std::endl
              << "v1: " << pos1 << std::endl
              << "v2: " << pos2 << std::endl
              << "normal: " << normal << std::endl
              << "reflexion_indx: " << reflexionIndex << std::endl;
}


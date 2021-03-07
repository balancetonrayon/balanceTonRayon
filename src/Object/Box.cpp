#include "Box.hpp"

// A Compléter - importé et refactoré de scratchapixel, mais manque l'emission des rayons créés
// (code )
/*void Box::intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                    std::vector<Ray> &rays) const {
    float tmin, tmax, tymin, tymax, tzmin, tzmax;

    tmin = (bounds[r.sign[0]].x - r.orig.x) * r.invdir.x;
    tmax = (bounds[1 - r.sign[0]].x - r.orig.x) * r.invdir.x;
    tymin = (bounds[r.sign[1]].y - r.orig.y) * r.invdir.y;
    tymax = (bounds[1 - r.sign[1]].y - r.orig.y) * r.invdir.y;

    if ((tmin > tymax) || (tymin > tmax)) return;
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;

    tzmin = (bounds[r.sign[2]].z - r.orig.z) * r.invdir.z;
    tzmax = (bounds[1 - r.sign[2]].z - r.orig.z) * r.invdir.z;

    if ((tmin > tzmax) || (tzmin > tmax)) return;
    if (tzmin > tmin) tmin = tzmin;
    if (tzmax < tmax) tmax = tzmax;

    t = tmin;
    if (t < 0) {
        t = tmax;
        if (t < 0) return;
    }
    inter.objColor = this->color;
    inter.objAlbedo = this->albedo;
    inter.objReflexionIndex = this->reflexionIndex;
    inter.objTransparency = this->transparency;
}*/

std::ostream &Box::printInfo(std::ostream &os) const {
    return os << "  - Box -" << std::endl
              << "v0: " << pos << std::endl
              << "v1: " << pos1 << std::endl
              << "v2: " << pos2 << std::endl
              << "v3: " << pos3;
}


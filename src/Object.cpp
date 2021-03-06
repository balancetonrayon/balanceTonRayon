#include "Object.hpp"

#include <cmath>
#include <memory>

#include <glm/gtc/constants.hpp>

#include "utils.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#define KEPSILON 0.00001

std::ostream &Light::printInfo(std::ostream &os) const {
    return os << "Light: in " << pos << ", of color: " << color;
}

void DirectLight::outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const {
    Ray ray;
    ray.setInitPt(hitPt);
    ray.setDir(glm::normalize(pos - hitPt));
    ray.setColor(color * intensity);
    rays.push_back(ray);
}

void SpotLight::outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const {
    Ray ray;
    ray.setInitPt(hitPt);
    ray.setDir(glm::normalize(pos - hitPt));
    ray.setColor(color * static_cast<float>(intensity / (4 * glm::pi<float>() *
                                                         glm::dot(pos - hitPt, pos - hitPt))));
    rays.push_back(ray);
}

void AreaLight::outboundRays(const glm::vec3 &hitPt, std::vector<Ray> &rays) const {
    Ray ray;
    ray.setInitPt(hitPt);
    ray.setDir(glm::normalize(pos - hitPt));
    ray.setColor(color * std::min(255.0f, static_cast<float>(
                                              intensity / (4 * glm::pi<float>() *
                                                           glm::dot(pos - hitPt, pos - hitPt)))));
    rays.push_back(ray);
}

Ray Camera::genRay(const float &x, const float &y) {
    if (x > resX || y > resY || x < 0 || y < 0) throw Camera::pixel_out_of_range();

    glm::vec3 rDir = dir * focalLength + hv * (float)(y / resY - 0.5) * sizeY +
                     vv * (float)(x / resX - 0.5) * sizeX;
    return Ray(pos, rDir);
}

std::ostream &Camera::printInfo(std::ostream &os) const {
    return os << "  --  Camera  -- " << std::endl
              << "at " << pos << ", of size: " << sizeX << std::endl
              << "vertical: " << vv << " horizontal: " << hv << std::endl
              << "focalLength: " << focalLength << " direction: " << dir << std::endl;
}

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

std::ostream &Polygon::printInfo(std::ostream &os) const {
    os << "  - Polygon -  " << std::endl;
    int i = 0;
    for (glm::vec3 vertex : vertices) {
        os << "v" << i++ << ": " << vertex << std::endl;
    }
    os << "normal: " << normal << std::endl;
    return os;
}

std::ostream &PolygonMesh::printInfo(std::ostream &os) const {
    std::string stream;
    os << "  - PolygonMesh - \n"
       << "Number of triangles: " << std::to_string(polygons.size()) << '\n';
    for (Polygon poly : polygons) {
        os << poly << std::endl;
    }
    return os << stream;
}

void TriangleMesh::intersect(const Ray &iRay, const std::shared_ptr<Light> &ltSrc, Inter &inter,
                             std::vector<Ray> &rays) const {
    float minDistance = INFINITY;
    Inter interTemp;
    for (Triangle triangle : triangles) {
        std::vector<Ray> raysTemp;
        triangle.intersect(iRay, ltSrc, interTemp, raysTemp);

        // check that intersection is non void and look for minimum value
        if (interTemp.id != -1 && interTemp.id < minDistance) {

            minDistance = interTemp.id;
            inter = Inter(interTemp);
            rays = raysTemp;
        }
    }
}
std::ostream &TriangleMesh::printInfo(std::ostream &os) const {
    std::string stream;
    os << "  - TriangleMesh - \n"
       << "Number of triangles: " << std::to_string(triangles.size()) << '\n';
    for (Triangle triangle : triangles) {
        os << triangle << std::endl;
    }
    return os;
}
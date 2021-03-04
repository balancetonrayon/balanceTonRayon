#include "Object.hpp"

#include <cmath>
#include <memory>

#include <glm/gtc/constants.hpp>

#include "utils.hpp"

#define KEPSILON 0.00001

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
// problème de performances : passer le vecteur en référence - à finir
std::vector<Ray> SpotLight::outboundRays(const glm::vec3 hitPt) const {
    std::vector<Ray> rays;
    Ray ray;
    ray.initPt = hitPt;
    ray.dir = glm::normalize(pos - hitPt);
    ray.color =
        color *
        static_cast<float>(intensity / (4 * glm::pi<float>() * glm::dot(pos - hitPt, pos - hitPt)));
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
        if (x > resX || y > resY || x < 0 || y < 0) throw Camera::pixel_out_of_range();
    } catch (Camera::pixel_out_of_range exception) {
        std::cout << "Pixel out of range" << std::endl;
    }

    glm::vec3 rDir = dir * focalLength + hv * (float)((float)y / resY - 0.5) * sizeY +
                     vv * (float)((float)x / resX - 0.5) * sizeX;

    // std::cout << Ray(pos, dir) << std::endl;
    return Ray(pos, rDir);
}

std::ostream &Camera::printInfo(std::ostream &os) const {
    return os << "Camera: in " << pos << ", of size: " << sizeX;
}

std::vector<Ray> Plane::intersect(const Ray iRay, const std::shared_ptr<Light> &ltSrc,
                                  Inter &inter) const {
    std::vector<Ray> rays;
    /*if (glm::dot(iRay.dir, normal) > 0)
        normal = -normal;*/

    // true if there is an intersection, false if there is none
    bool intersect = glm::intersectRayPlane(iRay.initPt, iRay.dir, pos, normal, inter.id);
    if (intersect) {
        glm::vec3 intersectPt = iRay.initPt + inter.id * iRay.dir;
        inter.normal = normal;

        Ray oRay = ltSrc->outboundRays(intersectPt)[0];

        inter.ld = glm::distance(intersectPt, ltSrc->pos);
        inter.rColor = oRay.color;
        rays.push_back(oRay);
        inter.objColor = this->color;
        inter.objReflexionIndex = this->reflexionIndex;
        inter.objTransparency = this->transparency;
    }
    return rays;
}

std::ostream &Plane::printInfo(std::ostream &os) const {
    return os << "   - Plan -" << std::endl
              << "at: " << pos << std::endl
              << "normal: " << normal << std::endl
              << "albedo: " << albedo << std::endl
              << "reflexion: " << reflexionIndex;
}

std::vector<Ray> Sphere::intersect(const Ray iRay, const std::shared_ptr<Light> &ltSrc,
                                   Inter &inter) const {
    std::vector<Ray> rays;

    glm::vec3 intersectPt;
    bool intersect =
        glm::intersectRaySphere(iRay.initPt, iRay.dir, pos, radius, intersectPt, inter.normal);
    if (intersect) {
        inter.id = glm::distance(iRay.initPt, intersectPt);
        // std::cout << "sphere distance: " << iDistance;
        Ray oRay = ltSrc->outboundRays(intersectPt)[0];
        inter.ld = glm::distance(intersectPt, ltSrc->pos);
        inter.rColor = oRay.color;
        /*std::vector<Ray> rays;
        std::cout << ray << std::endl
                  << *this << std::endl
                  << intersectPt << std::endl
                  << distance
                  << std::endl
                  << std::endl;*/
        inter.objColor = this->color;
        inter.objReflexionIndex = this->reflexionIndex;
        inter.objTransparency = this->transparency;
        inter.objAlbedo = this->albedo;
        rays.push_back(oRay);
    }
    return rays;
}

std::ostream &Sphere::printInfo(std::ostream &os) const {
    return os << "  - Sphere -" << std::endl
              << "at: " << pos << std::endl
              << "radius: " << radius << std::endl
              << "albedo: " << albedo;
}

std::vector<Ray> Triangle::intersect(const Ray iRay, const std::shared_ptr<Light> &ltSrc,
                                     Inter &inter) const {
    std::vector<Ray> rays;

    bool intersect = true;

    // Intersect or not ? Müller Trumbore algorithm
    glm::vec3 v0v1 = pos1 - pos;
    glm::vec3 v0v2 = pos2 - pos;
    glm::vec3 pvec = glm::cross(iRay.dir, v0v2);
    float det = glm::dot(v0v1, pvec);

    // ray and triangle are parallel if det is close to 0
    if (fabs(det) < KEPSILON) return rays;
    float invDet = 1 / det;

    glm::vec3 tvec = iRay.initPt - pos;
    float u = glm::dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) return rays;

    glm::vec3 qvec = glm::cross(tvec, v0v1);
    float v = glm::dot(iRay.dir, qvec) * invDet;
    if (v < 0 || u + v > 1) return rays;

    // distance to intersection
    float t = glm::dot(v0v2, qvec) * invDet;
    if (t < 0) return rays;

    if (intersect) {
        // std::cout << "in";
        inter.id = t;
        glm::vec3 intersectPt = iRay.initPt + inter.id * iRay.dir;
        inter.normal = normal;
        Ray oRay = ltSrc->outboundRays(intersectPt)[0];
        inter.ld = glm::distance(intersectPt, ltSrc->pos);
        inter.rColor = oRay.color;
        // std::cout << oRay.color<<std::endl;
        inter.objAlbedo = this->albedo;
        inter.objColor = this->color;
        inter.objReflexionIndex = this->reflexionIndex;
        inter.objTransparency = this->transparency;
        rays.push_back(oRay);
    }
    return rays;
}

std::ostream &Triangle::printInfo(std::ostream &os) const {
    return os << "  - Triangle -" << std::endl
              << "v0: " << pos << std::endl
              << "v1: " << pos1 << std::endl
              << "v2: " << pos2 << std::endl
              << "normal: " << normal << std::endl
              << "reflexion_indx: " << reflexionIndex << std::endl;
}

// A CHANGER
std::vector<Ray> Box::intersect(const Ray iRay, const std::shared_ptr<Light> &ltSrc,
                                Inter &inter) const {
    /*float tmin = (min.x - r.orig.x) / r.dir.x;
    float tmax = (max.x - r.orig.x) / r.dir.x;

    if (tmin > tmax) swap(tmin, tmax);

    float tymin = (min.y - r.orig.y) / r.dir.y;
    float tymax = (max.y - r.orig.y) / r.dir.y;

    if (tymin > tymax) std::swap(tymin, tymax);

    if ((tmin > tymax) || (tymin > tmax)) return false;

    if (tymin > tmin) tmin = tymin;

    if (tymax < tmax) tmax = tymax;

    float tzmin = (min.z - r.orig.z) / r.dir.z;
    float tzmax = (max.z - r.orig.z) / r.dir.z;

    if (tzmin > tzmax) std::swap(tzmin, tzmax);

    if ((tmin > tzmax) || (tzmin > tmax)) return false;

    if (tzmin > tmin) tmin = tzmin;

    if (tzmax < tmax) tmax = tzmax;

    return true;*/
    inter.objColor = this->color;
    inter.objAlbedo = this->albedo;
    inter.objReflexionIndex = this->reflexionIndex;
    inter.objTransparency = this->transparency;
    return *(new std::vector<Ray>);
}

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
    for (glm::vec3 vertice : vertices) {
        os << "v" << i++ << ": " << vertice << std::endl;
    }
    os << "normal: " << normal << std::endl;
    return os;
}

// TODO: à compléter
std::ostream &PolygonMesh::printInfo(std::ostream &os) const {
    std::string stream;
    os << "  - PolygonMesh - \n"
       << "Number of triangles: " << std::to_string(polygons.size()) << '\n';
    for (Polygon poly : polygons) {
        os << poly << std::endl;
    }
    return os << stream;
}

std::vector<Ray> TriangleMesh::intersect(const Ray iRay, const std::shared_ptr<Light> &ltSrc,
                                         Inter &inter) const {
    float minDistance = INFINITY;
    Inter interTemp;
    std::vector<Ray> rays;
    for (Triangle triangle : triangles) {
        // std::cout << "test";
        std::vector<Ray> raysTemp = triangle.intersect(iRay, ltSrc, interTemp);
        // check that intersection is non void and look for minimum value
        if (interTemp.id != -1 && interTemp.id < minDistance) {
            // std::cout << interTemp.id << " ";
            minDistance = interTemp.id;
            inter = Inter(interTemp);
            rays = raysTemp;
            // std::cout << rays.size() << " ";
        }
    }

    return rays;
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
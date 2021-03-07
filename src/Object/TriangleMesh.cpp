#include "TriangleMesh.hpp"

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

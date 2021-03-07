#include "PolygonMesh.hpp"

std::ostream &PolygonMesh::printInfo(std::ostream &os) const {
    std::string stream;
    os << "  - PolygonMesh - \n"
       << "Number of triangles: " << std::to_string(polygons.size()) << '\n';
    for (Polygon poly : polygons) {
        os << poly << std::endl;
    }
    return os << stream;
}

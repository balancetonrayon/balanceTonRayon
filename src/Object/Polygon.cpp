#include "Polygon.hpp"

std::ostream &Polygon::printInfo(std::ostream &os) const {
    os << "  - Polygon -  " << std::endl;
    int i = 0;
    for (glm::vec3 vertex : vertices) {
        os << "v" << i++ << ": " << vertex << std::endl;
    }
    os << "normal: " << normal << std::endl;
    return os;
}



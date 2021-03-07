#include "Light.hpp"

std::ostream &Light::printInfo(std::ostream &os) const {
    return os << "Light: in " << pos << ", of color: " << color;
}


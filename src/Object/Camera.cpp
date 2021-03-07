#include "Camera.hpp"

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


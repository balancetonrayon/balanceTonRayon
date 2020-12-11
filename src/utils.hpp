#pragma once
#include <opencv2/opencv.hpp>
#include <glm/vec3.hpp>

inline std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec)
{
    os << "{"
        << vec.x << " " << vec.y << " " << vec.z
        << "}";

    return os;
}

namespace detail
{

inline cv::Vec3b glm2cv(glm::vec3 in)
{
    return cv::Vec3b(in.x, in.y, in.z);
}

}

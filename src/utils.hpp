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

/*inline cv::Vec3b glm::vec3::(cv::Vec3b){
    return cv::Vec3b(x, y, z);
}*/
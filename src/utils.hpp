#pragma once
#include <opencv2/opencv.hpp>
#include <glm/vec3.hpp>

inline std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec) {
    os << "{"
       << vec.x << " " << vec.y << " " << vec.z
       << "}";

    return os;
}

namespace detail {

    inline cv::Vec3b glm2cv(const glm::vec3 &in) {
        return cv::Vec3b(in.x, in.y, in.z);
    }

    inline glm::vec3 cv2glm(const cv::Vec3b &in) {
        return glm::vec3(in[0], in[1], in[2]);
    }

    inline glm::vec3 mult(const glm::vec3 &lhs, const glm::vec3 &rhs) {
        return glm::vec3(lhs.x*rhs.x, lhs.y*rhs.y, lhs.z*rhs.z);
    }

} // namespace detail

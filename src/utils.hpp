/**
 * @file utils.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief
 * @version 0.1
 * @date 2021-03-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <glm/vec3.hpp>
#include <opencv2/opencv.hpp>

/**
 * @brief
 *
 * @param os
 * @param vec
 * @return std::ostream&
 */
inline std::ostream &operator<<(std::ostream &os, const glm::vec3 &vec) {
    os << "{" << vec.x << " " << vec.y << " " << vec.z << "}";

    return os;
}

/**
 * @brief
 *
 */
namespace detail {

/**
 * @brief
 *
 * @param in
 * @return cv::Vec3b
 */
inline cv::Vec3b glm2cv(const glm::vec3 &in) { return cv::Vec3b(in.x, in.y, in.z); }

/**
 * @brief
 *
 * @param in
 * @return glm::vec3
 */
inline glm::vec3 cv2glm(const cv::Vec3b &in) { return glm::vec3(in[0], in[1], in[2]); }

/**
 * @brief
 *
 * @param lhs
 * @param rhs
 * @return glm::vec3
 */
inline glm::vec3 mult(const glm::vec3 &lhs, const glm::vec3 &rhs) {
    return glm::vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

}  // namespace detail

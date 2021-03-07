/**
 * @file utils.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief Small file which defines a few utility functions
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#include <glm/vec3.hpp>

#define KEPSILON 0.00001

/**
 * @brief Overload of the operator << for the glm::vec3
 *
 * @param os
 * @param vec the vector to print
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
 * @brief Method to multiply vectors element by element
 *
 * @param lhs the first vector
 * @param rhs the second vector
 * @return glm::vec3
 */
inline glm::vec3 mult(const glm::vec3 &lhs, const glm::vec3 &rhs) {
    return glm::vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

}  // namespace detail

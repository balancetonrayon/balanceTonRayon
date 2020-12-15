#pragma once

#include <glm/vec3.hpp>
#include "utils.hpp"

struct Ray
{
    glm::vec3 initPt;
    glm::vec3 dir; //normalized

    Ray() : initPt(glm::vec3(0, 0, 0)), dir(glm::normalize(glm::vec3(1, 0, 0))){};
    Ray(glm::vec3 initPt, glm::vec3 dir) : initPt(initPt), dir(glm::normalize(dir)){};

    friend std::ostream &operator<<(std::ostream &stream, Ray const &ray)
    {
        return stream << "Ray of initPt: " << ray.initPt << " and direction: " << ray.dir;
    }
};

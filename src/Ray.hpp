#pragma once
#include <glm/vec3.hpp>

struct Ray
{
    glm::vec3 initPt;
    glm::vec3 dir; //in unit length

    Ray();

    Ray(glm::vec3 initPt, glm::vec3 dir) : initPt(initPt), dir(dir){};
};
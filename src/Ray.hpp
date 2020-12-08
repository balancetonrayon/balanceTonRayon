#pragma once
#include <glm/vec3.hpp>

struct Ray
{
    glm::vec3 initPt;
    glm::vec3 dir; //normalized

    Ray();

    Ray(glm::vec3 initPt, glm::vec3 dir) : initPt(initPt), dir(dir){};
};
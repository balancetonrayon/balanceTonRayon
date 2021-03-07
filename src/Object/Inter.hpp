#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <memory>
#include <vector>

#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>

#include "Ray.hpp"
#include "Texture.hpp"

/**
 * @class Inter
 * @brief This class contains all the information of an intersection.
 *
 */
class Inter {
public:
    /**
     * @brief the distance between the intersection and the object.
     *
     */
    float id;

    //! A public variable.
    /**
     * @brief ld is the distance between the intersection and the light.
     *
     */
    float ld;

    //! A public variable.
    /**
     * @brief normal is the normal at the intersection.
     *
     */
    glm::vec3 normal;

    //! A public variable.
    /**
     * @brief rColor is the color of the ray at the intersection
     *
     */
    glm::vec3 rColor;

    //! A public variable.
    /**
     * @brief objColor is the color of the object responsible for the intersection
     *
     */
    glm::vec3 objColor;

    //! A public variable
    /**
     * @brief The reflexion index of the object responsible for intersection
     *
     */
    float objReflexionIndex;

    //! A public variable
    /**
     * @brief The transparency of the object responsible for intersection
     *
     */
    float objTransparency;

    //! A public variable
    /**
     * @brief The albedo of the object responsible for intersection
     *
     */
    float objAlbedo;

    //! The default constructor.
    /**
     * @brief The intersection distances are chosen negative and the normal and the color are
     * (0,0,0) vectors
     *
     */
    Inter() : id(-1), ld(-1), normal(glm::vec3()), rColor(glm::vec3()){};

    //! The specialized constructor.
    /**
     s* @brief Creates an intersection with the desired parameters

     */
    explicit Inter(float i, float l, glm::vec3 n, glm::vec3 c)
        : id(i), ld(l), normal(n), rColor(c){};
};

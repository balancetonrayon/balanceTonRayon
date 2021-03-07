#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <iostream>
#include <memory>
#include <vector>

#include <glm/geometric.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>

#include "PhysicalObject.hpp"
#include "Ray.hpp"
#include "Texture.hpp"

//!  The Camera class.
/**
  \class Camera
  @brief It represents and contains all the information about the camera.
*/
class Camera : public PhysicalObject {
public:
    /**
     * @brief Normal direction of the camera.
     *
     */
    glm::vec3 dir;

    /**
     * @brief Vertical vector of the camera's screen.
     * @sa hv
     *
     */
    glm::vec3 vv;

    /**
     * @brief Vertical vector of the camera's screen.
     * @sa vv
     *
     */
    glm::vec3 hv;

    /**
     * @brief the size of the screen on the x axis
     *
     */
    float sizeX;
    /**
     * @brief the size of the screen on the y axis
     *
     */
    float sizeY;

    /**
     * @brief the resolution of the screen on the x axis
     *
     */
    unsigned resX;
    /**
     * @brief the resolution of the screen on the y axis
     *
     */
    unsigned resY;

    /**
     * @brief the distance between the source and the screen
     *
     */
    float focalLength;

    /**
     * @brief Get the Number Of Pixels object
     * 
     * @return int 
     */
    int getNumberOfPixels() const { return resX * resY; }
    
    /**
     * @brief A normal member taking two arguments and returning the generated ray
     *
     * @param x the number of the x pixel
     * @param y the number of the y pixel
     * @return Ray
     */
    Ray genRay(const float &x, const float &y);

    /**
     * @brief Construct a Camera at (0, 0, 0) with screen of size (1, 1) and (1000, 1000)
      pixels 1 away from the image sensor. The camera is assumed horizontal.
     *
     * @param pos the position of the source of the camera rays
     * @param dir the direction of the camera (normal to the screen)
     * @param sx the size along the x axis
     * @param sy the size along the y axis
     * @param rx the resolution along the x axis
     * @param ry the resolution alongs the y axis
     * @param fL the focal length
     */
    explicit Camera(glm::vec3 pos = glm::vec3(), glm::vec3 dir = glm::vec3(1, 0, 0), float sx = 1,
                    float sy = 1, unsigned rx = 1000, unsigned ry = 1000, float fL = 1)
        : PhysicalObject(pos),
          dir(glm::normalize(dir)),
          sizeX(sx),
          sizeY(sy),
          resX(rx),
          resY(ry),
          focalLength(fL) {
        if (dir[2]) std::cout << "Erreur, rotation suivant l'axe vertical interdite" << std::endl;
        vv = glm::vec3(0, 0, -1);
        if (!dir[0]) {
            if (dir[1] > 0) {
                hv = glm::vec3(-1, 0, 0);
            }
            if (dir[1] < 0) {
                hv = glm::vec3(1, 0, 0);
            }
        } else if (!dir[1]) {
            if (dir[0] > 0) {
                hv = glm::vec3(0, 1, 0);
            }
            if (dir[0] < 0) {
                hv = glm::vec3(0, -1, 0);
            }
        } else {
            float y = std::sqrt(1 / (1 + dir[2] * dir[2] / (dir[1] * dir[1])));
            hv = glm::vec3(-dir[2] / dir[1] * y, y, 0);
        }
    }

protected:
    /**
     * @brief  A normal member taking one argument and returning the information about an object. It
     * replaces the pure virtual member of PhysicalObject
     *
     * @sa PhysicalObject
     * @param os the current ostream
     * @return The information of the object as an ostream
     */
    std::ostream &printInfo(std::ostream &os) const override;

    class pixel_out_of_range {};
};

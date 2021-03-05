#pragma once
#include <vector>

#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

/**
 * @class Texture
 * @brief A texture associated to another object
 *
 */
class Texture {
public:
    virtual glm::vec4 getColor(const glm::vec3 &pos) const = 0;
};

/**
 * @class Image
 * @brief A class representing an image
 *
 */
class Image : public Texture {
protected:
    //! A protected variable.
    /**
      @brief The origin of the image (top left)
    */
    glm::vec3 origin;

    //! A protected variable.
    /**
      @brief The direction of the vertical axis of the image.
      @sa wVec
    */
    glm::vec3 hVec;
    /**
     * @brief The norm of the hVec vector. For faster computing.
     *
     */
    float hVecNorm;

    //! A protected variable.
    /**
      @brief The direction of the horizontal axis of the image.
      @sa hVec
    */
    glm::vec3 wVec;
    /**
     * @brief The norm of the wVec vector. For faster computing.
     *
     */
    float wVecNorm;

    /**
     * @brief The height of the picture in pixels.
     *
     */
    int height;

    /**
     * @brief The width of the picture in pixels.
     *
     */
    int width;

    //! A protected variable.
    /**
      @brief The pixels of the image.
    */
    std::vector<unsigned char> pixels;

public:
    /**
     * @brief Get the height of the picture in pixels.
     *
     * @return int
     */
    int getPixHeight() { return this->height; }

    /**
     * @brief Get the width of the picture in pixels.s
     *
     * @return int
     */
    int getPixWidth() { return this->height; }

    /**
     * @brief Set the Pixels of the image
     * 
     * @param pix the pixels read from an image
     */
    void setPixels(const std::vector<unsigned char> &pix) { this->pixels = pix; }

    /**
     * @brief Get the potential Pixel Ids (vertical and horizontal)
     *
     * @param intersectPt the coordinates of the intersect point
     * @param hPix vertical pixel id modified to the right value
     * @param wPix horizontal pixel id modified to the right value
     */
    void getPixelId(const glm::vec3 &intersectPt, int &hPix, int &wPix) const;

    /**
     * @brief Function which returns if the pixel defined by hPix (vertical id) and wPix (horizonal
     * id) is within the picture's boundaries.
     *
     * @param hPix vertical id (height)
     * @param wPix horizontal id (width)
     * @return true if the pixel is in the pictures boundaries
     * @return false if the pixel is not
     */
    bool isInPicture(const int &hPix, const int &wPix) const;

    /**
     * @brief Get the Pixel corresponding to a column (hPix) and a row (wPix)
     *
     * @param hPix id of the column
     * @param wPix id of the row
     * @param color glm::vec4: RGBA
     */
    void getPixel(const int &hPix, const int &wPix, std::vector<unsigned char> color) const;

    /**
     * @brief Get the Color object
     *
     * @param pos
     * @return glm::vec4
     */
    glm::vec4 getColor(const glm::vec3 &pos) const override;

protected:
    //! A normal member taking one argument and returning the information about
    //! an object. It replaces the pure virtual member of PhysicalObject
    /**
    @brief
      @param os the current ostream
      @return The information of the object as an ostream
    */
    // std::ostream &printInfo(std::ostream &os) const override;
};
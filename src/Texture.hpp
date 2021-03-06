/**
 * @file Texture.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief The file defines the texture of the objects
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 *
 */
#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <vector>

#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "ImgHandler.hpp"
#include "utils.hpp"

/**
 * @class Texture
 * @brief A texture associated to another object
 *
 */
class Texture {
public:
    /**
     * @brief Get the Color of the texture at certain coordinates
     *
     * @param pos the coordinates of the intersection point.
     * @
     * @return glm::vec4
     */
    virtual glm::vec4 getColor(const glm::vec3 &pos, bool &onTexture) const = 0;

    /**
     * @brief
     *
     * @param stream
     * @param obj
     * @return std::ostream&
     */
    friend std::ostream &operator<<(std::ostream &stream, Texture const &tex) {
        return tex.printInfo(stream);
    }

protected:
    /**
     * @brief A pure virtual member returning the information about an object.
     *
     * @param os
     * @return std::ostream&
     */
    virtual std::ostream &printInfo(std::ostream &os) const = 0;
};

/**
 * @class Image
 * @brief A class representing an image
 *
 */
class Image : public Texture {
protected:
    /**
      @brief The origin of the image (top left)
    */
    glm::vec3 origin;

    /**
      @brief The direction of the vertical axis of the image.
      @sa wVec
    */
    glm::vec3 hVec;
    /**
     * @brief The square of the norm of the hVec vector. For faster computing.
     *
     */
    float hVecNorm2;

    /**
      @brief The direction of the horizontal axis of the image.
      @sa hVec
    */
    glm::vec3 wVec;

    /**
     * @brief The square of the norm of the wVec vector. For faster computing.
     *
     */
    float wVecNorm2;

    /**
     * @brief The height of the picture in pixels.
     *@sa width
     */
    unsigned height;

    /**
     * @brief The width of the picture in pixels.
     *@sa height
     *
     */
    unsigned width;

    /**
     * @brief The pixels of the image.
     *
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
     * @brief Get the width of the picture in pixels.
     *
     * @return int
     */
    int getPixWidth() { return this->height; }

    /**
     * @brief Get the Pixels of the image.
     *
     * @return std::vector<unsigned char>
     */
    std::vector<unsigned char> getPixels() { return this->pixels; }

    /**
     * @brief Saves the pixels of the image as a PNG.
     *
     * @param filename
     */
    void savePixels(char *filename) {
        ImgHandler ImgHandler;
        ImgHandler.writePNG(filename, this->pixels, this->height, this->width);
    }

    /**
     * @brief Set the Pixels of the image.
     *
     * @param pix the pixels read from an image
     */
    void setPixels(const std::vector<unsigned char> &pix) { this->pixels = pix; }

    /**
     * @brief Get the potential Pixel Ids (vertical and horizontal).
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
     * @brief Get the Pixel corresponding to a column (hPix) and a row (wPix).
     *
     * @param hPix id of the column
     * @param wPix id of the row
     * @param color glm::vec4: RGBA in [|0, 255|]
     */
    void getPixel(const int &hPix, const int &wPix, std::vector<unsigned char> &color) const;

    /**
     * @brief Get the Color of the image at some coordinates.
     *
     * @param pos the coordinates
     * @param onTexture true if the image is defined at these coordinates - False by DEFAULT
     * @return glm::vec4 - R G B and transparency in [0,1]
     */
    glm::vec4 getColor(const glm::vec3 &pos, bool &onTexture) const override;

    /**
     * @brief Construct a new Image object. WVEC SHOULD BE NORMALIZED
     *
     * @param filename the name of the file in std::string
     * @param origin the coordinates of the origin of the image (top-left corner)
     * @param hVec the vertical vector of the image
     * @param wVec the horizontal vector of the image. Should be NORMALIZED for the ratios of the
     * image not to be modified
     */
    explicit Image(const std::string &filename, const glm::vec3 &origin, const glm::vec3 &hVec,
                   const glm::vec3 &wVec)
        : origin(origin), hVec(hVec), hVecNorm2(glm::l2Norm(hVec) * glm::l2Norm(hVec)) {
        ImgHandler ImgHandler;
        this->setPixels(ImgHandler.readPNG(filename, this->height, this->width));

        this->wVec = wVec * glm::l2Norm(this->hVec) * (float)this->width / (float)this->height;
        this->wVecNorm2 = glm::l2Norm(this->wVec);
        this->wVecNorm2 *= wVecNorm2;

        // If the image is not a square, change the origin
        if (this->width != this->height) {
            if (glm::cross(hVec, wVec)[0] > 0) {
                std::cout << "Case 3 ";
                std::cout << glm::l2Norm(this->hVec) << " " << glm::l2Norm(this->wVec) << std::endl;
                this->origin[1] =
                    origin[1] + glm::l2Norm(this->hVec) / 2.0f - glm::l2Norm(this->wVec) / 2.0f;

            } else {
                std::cout << "Case 4 ";
                this->origin[1] =
                    origin[1] - glm::l2Norm(this->hVec) / 2.0f + glm::l2Norm(this->wVec) / 2.0f;
            }
        }
        std::cout << this->origin << std::endl;
        std::cout << *this << std::endl;
    }

protected:
    /**
     * @brief A normal member returning the information about an object. It replaces the pure
     * virtual member of Texture
     *
     * @param os
     * @return std::ostream&
     */
    std::ostream &printInfo(std::ostream &os) const override;
};
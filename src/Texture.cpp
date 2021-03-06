/**
 * @file Texture.cpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief This File contains the implementation of the templates defined in the .hpp.
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "Texture.hpp"

void Image::getPixelId(const glm::vec3 &intersectPt, int &hPix, int &wPix) const {
    glm::vec3 pos = intersectPt - this->origin;
    // std::cout << pos << " " << wVecNorm2 << std::endl;

    float posNorm = glm::l2Norm(pos);
    // std::cout << "Norm: " << posNorm << std::endl;
    float hAxis = glm::dot(pos, hVec) / hVecNorm2;
    float wAxis = glm::dot(pos, wVec) / wVecNorm2;
    // std::cout << "Haxis: " << hAxis << " Waxis: " << wAxis << std::endl;
    hPix = hAxis * (float)height;
    wPix = wAxis * (float)width;
    // std::cout << "Hpix: " << hPix << " Wpix: " << wPix << std::endl;
}

bool Image::isInPicture(const int &hPix, const int &wPix) const {
    return hPix >= 0 && wPix >= 0 && hPix < height && wPix < width;
}

void Image::getPixel(const int &hPix, const int &wPix, std::vector<unsigned char> &color) const {
    int id = (hPix * width + wPix) * 4;
    color = std::vector<unsigned char>(this->pixels.begin() + id, this->pixels.begin() + id + 4);
}

glm::vec4 Image::getColor(const glm::vec3 &pos, bool &onTexture) const {
    int hPix, wPix;
    std::vector<unsigned char> color(4);

    getPixelId(pos, hPix, wPix);
    if (isInPicture(hPix, wPix)) {
        onTexture = true;
        getPixel(hPix, wPix, color);
    }
    return glm::vec4(color[0] / 255.0f, color[1] / 255.0f, color[2] / 255.0f,
                     1.0f - color[3] / 255.0f);
}

std::ostream &Image::printInfo(std::ostream &os) const {
    return os << "  --  Image  --" << std::endl
              << "at: " << origin << std::endl
              << "width: " << width << std::endl
              << "height: " << height << std::endl
              << "hVec: " << hVec << std::endl
              << "wVec: " << wVec << std::endl;
}

glm::vec4 CheckedPattern2D::getColor(const glm::vec3 &pos, bool &onTexture) const {
    onTexture = (std::sin(std::abs(pos[0]+1)) > 0 && std::sin(std::abs(pos[1])+1) > 0);
    return glm::vec4(color[0], color[1], color[2], 0);
};

std::ostream &CheckedPattern2D::printInfo(std::ostream &os) const {
    return os << "  --  CheckedPattern3D  --" << std::endl << "color: " << color << std::endl;
}
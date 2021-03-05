#include "Texture.hpp"

void Image::getPixelId(const glm::vec3 &intersectPt, int &hPix, int &wPix) const {
    glm::vec3 pos = intersectPt - this->origin;
    float posNorm = glm::l2Norm(pos);

    float hAxis = glm::dot(pos, hVec) / (posNorm * hVecNorm);
    float vAxis = glm::dot(pos, wVec) / (posNorm * wVecNorm);

    hPix = 1 / hAxis * height;
    wPix = 1 / hAxis * width;
}

bool Image::isInPicture(const int &hPix, const int &wPix) const {
    return hPix >= 0 && wPix >= 0 && hPix < height && wPix < width;
}

void Image::getPixel(const int &hPix, const int &wPix, std::vector<unsigned char> color) const {
    int id = hPix * width + wPix;
    color = std::vector<unsigned char>(this->pixels.begin() + id, this->pixels.begin() + id + 4);
}

glm::vec4 Image::getColor(const glm::vec3 &pos) const {
    int hPix, wPix;
    std::vector<unsigned char> color;

    getPixelId(pos, hPix, wPix);
    isInPicture(hPix, wPix);
    getPixel(hPix, wPix, color);

    return glm::vec4(color[0], color[1], color[2], color[3]);
}
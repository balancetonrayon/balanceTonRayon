#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <glm/vec3.hpp>

#include "lodepng.h"

/**
 * @brief A class to read PNGs
 * @class ImgReader
 */
class ImgReader {
public:
    std::vector<unsigned char> readPNG(
        const char* filename /*, std::vector<std::vector<glm::vec3>>*/) {
        std::vector<unsigned char> image;  // the raw pixels
        unsigned width, height;

        // decode
        unsigned error = lodepng::decode(image, width, height, filename);

        // if there's an error, display it
        if (error)
            std::cout << "decoder error " << error << ": " << lodepng_error_text(error)
                      << std::endl;
        return image;
        // the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use
        // it as texture, draw it, ...
    }
};
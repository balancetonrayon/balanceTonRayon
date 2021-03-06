/**
 * @file ImgReader.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief A wrapper for the lodepng library. The code below is a slightly modifed version of the
 * code contained in lodepng's documentation
 * @version 1
 * @date 2021-03-03
 *
 */

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
    /**
     * @brief A method to read a file with its name.
     *
     * @param filename the name of the file as a char array
     * @param height the image as a vector of unsigned chars
     * @param width the height of the image (in pixels)
     * @return std::vector<unsigned char> the pixels of the image
     */
    std::vector<unsigned char> readPNG(const char* filename, unsigned& height, unsigned& width) {
        std::vector<unsigned char> image;  // the raw pixels

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

    /**
     * @brief A method to write an unsigned chat vector to PNG
     *
     * @param filename the name of the file
     * @param image the image as a vector of unsigned chars
     * @param height the height of the image (in pixels)
     * @param width the
     */
    void writePNG(const char* filename, std::vector<unsigned char> image, unsigned& height,
                  unsigned& width) {
        // Encode the image
        unsigned error = lodepng::encode(filename, image, width, height);

        // if there's an error, display it
        if (error)
            std::cout << "encoder error " << error << ": " << lodepng_error_text(error)
                      << std::endl;
    }
};
/**
 * @file main.cpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief The starting point of our project
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <chrono>
#include <fstream>
#include <random>
#include <string>

#include "ObjParser.hpp"
#include "Parser.hpp"
#include "RayTracer.hpp"

Scene loadScene(std::string filename) {
    Scene scene;

    std::ifstream ifs(filename);

    if (!ifs.is_open()) {
        throw std::runtime_error(
            "The file representing your scene does not exist. Please check the path to your file ");
    } else {
        std::string xmlData((std::istreambuf_iterator<char>(ifs)),
                            (std::istreambuf_iterator<char>()));

        Parser xmlParser(xmlData);

        std::cout << " --- Rendering : " << xmlParser.getName() << " ---" << std::endl;

        scene.setBackgroundColor(xmlParser.getBackgroundColor());
        scene.setMaxDepth(xmlParser.getMaxDepth());

        for (auto object : xmlParser.getObjects()) scene.addObject(object);

        for (auto source : xmlParser.getSources()) scene.addSource(source);

        scene.setCamera(xmlParser.getCamera());

        return scene;
    }
}

int main(int argc, const char **argv) {
    std::cout << "Starting the ray-Tracing Software by Atoli Huppé and Olivier Laurent" << std::endl
              << std::endl;
    if (argc == 1) {
        unsigned seed = (std::chrono::duration_cast<std::chrono::nanoseconds>(
                             std::chrono::system_clock::now().time_since_epoch()))
                            .count();
        std::uniform_real_distribution<float> distribution(0.0, 1.0);
        std::mt19937_64 rng(seed);

        float rdm = distribution(rng);

        if (rdm < 0.333) {
            std::cout
                << "Since no arguments have been given, generating 'A walk through the trees'. "
                   "Please find the output file in the data folder."
                << std::endl;

            Scene scene = loadScene("../data/walkTrees.xml");
            FixedAntiAliasingRayTracer AArt(true, scene.getMaxDepth(), 2);

            AArt.render(scene, "../data/AWalkThroughTheTrees.png");
        } else if (rdm < 0.666) {
            std::cout << "Since no arguments have been given, generating 'The Dalton Family'. "
                         "Please find the output file in the data folder."
                      << std::endl;

            Scene scene = loadScene("../data/daltons.xml");
            FixedAntiAliasingRayTracer AArt(true, scene.getMaxDepth(), 2);

            AArt.render(scene, "../data/daltons.png");
        } else {
            std::cout
                << "Since no arguments have been given, generating 'The White and Blue Billiard'. "
                   "Please find the output file in the data folder."
                << std::endl;

            Scene scene = loadScene("../data/billiard.xml");
            FixedAntiAliasingRayTracer AArt(true, scene.getMaxDepth(), 3);

            AArt.render(scene, "../data/billiard.png");
        }
    } else if (argc == 2) {
        std::cout << "Your file is going to be loaded. If you want, you may specify n - with "
                     "(n<5) - if you want some anti-anliasing."
                  << std::endl;
        Scene scene = loadScene(argv[1]);
        std::cout << scene.getColor();
        StdRayTracer srt(true, scene.getMaxDepth());

        srt.render(scene, argv[1]);
    } else if (argc >= 3) {
        std::cout << "Your file is going to be loaded." << std::endl;
        std::string filename = argv[1];
        Scene scene = loadScene(argv[1]);

        FixedAntiAliasingRayTracer AArt(true, scene.getMaxDepth(), std::stoi(argv[2]));

        size_t lastindex = filename.find_last_of(".");
        std::string rawname = filename.substr(0, lastindex);

        AArt.render(scene, "../data/" + rawname + ".png");
    }
    return 0;
}

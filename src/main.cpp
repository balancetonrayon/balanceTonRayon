/**
 * @file main.cpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief The starting point of our project
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <fstream>
#include <string>

#include "ObjParser.hpp"
#include "Parser.hpp"
#include "RayTracer.hpp"
//#include "ImgHandler.hpp"

/**
 * @brief
 *
 * @return Scene
 */
Scene daltons() {
    Scene scene;

    std::ifstream ifs("../data/daltons.xml");
    std::string xmlData((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    Parser xmlParser(xmlData);

    std::cout << xmlParser.getName() << std::endl;

    for (auto object : xmlParser.getObjects()) scene.addObject(object);

    for (auto source : xmlParser.getSources()) scene.addSource(source);

    scene.setCamera(xmlParser.getCamera());

    return scene;
}

Scene ataporte(std::string filename) {
    Scene scene(glm::vec3(235, 206, 135));
    /*ImgHandler ImgHandler;
    ImgHandler.readFile("image.png");*/
    return scene;
}

void AATest() {
    Scene scene = daltons();
    FixedAntiAliasingRayTracer AArt(true, 10, 2);

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }

    AArt.render(scene, "RayTracingAA.png");
}

void Cesart() {
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(
        glm::vec3(0.0, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(1, 1, 1), 0, 0, 0, 0.5);
    auto sphere1 =
        std::make_shared<Sphere>(glm::vec3(-0.11, 0, 0), glm::vec3(1, 1, 1), 0.1, 0, 0, 0.8, 0.22);

    std::string filename = "../data/cesar2.png";
    glm::vec3 origin(0.0, -0.5, 0.5);
    glm::vec3 hVec(0, 0, -1);
    glm::vec3 wVec(0, 1, 0);
    plane->setTexture(std::make_shared<Image>(filename, origin, hVec, wVec));

    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0), 0.1, 0.1, 1000,
                                           1000, 0.05);
    auto lightSource =
        std::make_shared<DirectLight>(glm::vec3(-5, 0, 10), glm::vec3(1, 1, 1), 2000);

    Scene scene;
    StdRayTracer stdrt;
    scene.addObject(plane);
    scene.addObject(sphere1);
    scene.addSource(lightSource);
    scene.setCamera(camera);

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }

    stdrt.render(scene, "Cesart.png");
}

void Cesar() {
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(
        glm::vec3(0.11, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(1, 1, 1), 0, 0, 0, 0.5);
    auto sphere1 =
        std::make_shared<Sphere>(glm::vec3(-0.11, 0, 0), glm::vec3(1, 1, 1), 0.05, 0, 0, 0.8, 0.22);
    std::string filename = "../data/crepon.png";

    glm::vec3 origin(0.05, -1, 1);
    glm::vec3 hVec(0, 0, -2);
    glm::vec3 wVec(0, 1, 0);
    plane->setTexture(std::make_shared<Image>(filename, origin, hVec, wVec));

    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0), 0.1, 0.1, 1000,
                                           1000, 0.1);
    auto lightSource =
        std::make_shared<DirectLight>(glm::vec3(-5, 0, 10), glm::vec3(1, 1, 1), 2000);

    Scene scene;
    StdRayTracer stdrt;
    scene.addObject(plane);
    scene.addObject(sphere1);
    scene.addSource(lightSource);
    scene.setCamera(camera);

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }

    stdrt.render(scene, "Crepon.png");
}

Scene testTexture() {
    Scene scene;

    std::ifstream ifs("../data/daltons.xml");
    std::string xmlData((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

    Parser xmlParser(xmlData);

    std::cout << xmlParser.getName() << std::endl;

    for (auto object : xmlParser.getObjects()) {
        object->setTexture(std::make_shared<CheckedPattern2D>(glm::vec3(0, 0, 1)));
        scene.addObject(object);
    }

    for (auto source : xmlParser.getSources()) scene.addSource(source);

    scene.setCamera(xmlParser.getCamera());

    return scene;
}

void test() {
    Scene scene = testTexture();
    StdRayTracer stdrt;

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }
    std::cout << *scene.getCamera() << std::endl;

    stdrt.render(scene, "Texture.png");
}

int main(int argc, const char **argv) {
    test();
    return 0;
}

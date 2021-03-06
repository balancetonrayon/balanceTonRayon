/**
 * @file main.cpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief 
 * @version 1
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ObjParser.hpp"
#include "RayTracer.hpp"
//#include "ImgHandler.hpp"

/**
 * @brief 
 * 
 * @return Scene 
 */
Scene daltons() {
    ObjParser parser;
    PolygonMesh mesh = parser.readObj("../data/cube.obj");

    // Scene scene(glm::vec3(235, 206, 135));
    Scene scene;

    auto plane = std::make_shared<Plane>(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(1, 1, 1),
                                         0, 0, 0.2, 0.25);

    auto sphere1 =
        std::make_shared<Sphere>(glm::vec3(6.16, 0.66, 1), glm::vec3(1, 1, 1), 1, 0, 0, 0.8, 0.22);
    auto sphere2 =
        std::make_shared<Sphere>(glm::vec3(5, 0, 0.66), glm::vec3(0, 1, 1), 0.66, 0, 0, 0.2, 0.2);
    auto sphere3 = std::make_shared<Sphere>(glm::vec3(4.16, 0.44, 0.20), glm::vec3(0, 0, 1), 0.20,
                                            0, 0, 0.1, 0.20);
    auto sphere4 = std::make_shared<Sphere>(glm::vec3(5.25, 3, 0.66), glm::vec3(1, 1, 1), 0.25,
                                            0.95, 1.5, 0, 0.05);

    // auto triangle1 = std::make_shared<Triangle>(
    //    glm::vec3(1.5, -0.5, -0.5), glm::vec3(1.5, 0.5, 0.5), glm::vec3(1.5, 0.5, -0.5));

    auto camera = std::make_shared<Camera>(glm::vec3(3, 0, 0.5), glm::vec3(1, 0, 0), 0.1, 0.1, 1000,
                                           1000, 0.05);
    auto lightSource = std::make_shared<DirectLight>(glm::vec3(0, 0, 10), glm::vec3(1, 1, 1), 2000);

    scene.addObject(plane);
    scene.addObject(sphere1);
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    // scene.addObject(sphere4);
    // TriangleMesh tMesh(mesh);
    // scene.addObject(std::make_shared<Triangle>(tMesh.getTriangles()[10]));
    // scene.addObject(std::make_shared<TriangleMesh>(tMesh));
    // scene.addObject(triangle1);
    scene.setCamera(camera);
    scene.addSource(lightSource);

    return scene;
}

Scene ataporte(std::string filename) {
    Scene scene(glm::vec3(235, 206, 135));
    /*ImgHandler ImgHandler;
    ImgHandler.readFile("image.png");*/
    return scene;
}

void test() {
    Scene scene = daltons();
    StdRayTracer stdrt;

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }

    stdrt.render(scene);
}

void AATest() {
    Scene scene = daltons();
    FixedAntiAliasingRayTracer AArt(2);

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }

    AArt.render(scene);
}

void Cesart() {
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(glm::vec3(0.0, 0, 0), glm::vec3(-1, 0, 0),
                                                           glm::vec3(1, 1, 1), 0, 0, 0, 0.5);
    auto sphere1 =
        std::make_shared<Sphere>(glm::vec3(-0.11, 0, 0), glm::vec3(1, 1, 1), 0.1, 0, 0, 0.8, 0.22);
    std::string filename = "../data/cesar2.png";
    std::string filenameW = "../data/cesar3.png";

    glm::vec3 origin(0.0, -0.5, 0.5);
    glm::vec3 hVec(0, 0, -1);
    glm::vec3 wVec(0, 1, 0);
    plane->setTexture(std::make_shared<Image>(filename, origin, hVec, wVec));

    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0), 0.1, 0.1, 1000,
                                           1000, 0.05);
    auto lightSource = std::make_shared<DirectLight>(glm::vec3(-5, 0, 10), glm::vec3(1, 1, 1), 2000);

    Scene scene;
    StdRayTracer stdrt;
    scene.addObject(plane);
    scene.addObject(sphere1);
    scene.addSource(lightSource);
    scene.setCamera(camera);

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }
    //std::cout << *(plane->getTexture()) << std::endl;
    
    //plane->getTexture()->savePixels(file_nameW);
    stdrt.render(scene);
}

void Cesar() {
    std::shared_ptr<Plane> plane = std::make_shared<Plane>(glm::vec3(0.11, 0, 0), glm::vec3(-1, 0, 0),
                                                           glm::vec3(1, 1, 1), 0, 0, 0, 0.5);
    auto sphere1 =
        std::make_shared<Sphere>(glm::vec3(-0.11, 0, 0), glm::vec3(1, 1, 1), 0.05, 0, 0, 0.8, 0.22);
    std::string filename = "../data/cesar2.png";
    std::string filenameW = "../data/cesar3.png";

    glm::vec3 origin(0.05, -0.5, 0.5);
    //permettre l'augmentation de la taille de l'image
    glm::vec3 hVec(0, 0, -1);
    glm::vec3 wVec(0, 1, 0);
    plane->setTexture(std::make_shared<Image>(filename, origin, hVec, wVec));

    auto camera = std::make_shared<Camera>(glm::vec3(0, 0, 0), glm::vec3(-1, 0, 0), 0.1, 0.1, 1000,
                                           1000, 0.1);
    auto lightSource = std::make_shared<DirectLight>(glm::vec3(-5, 0, 10), glm::vec3(1, 1, 1), 2000);

    Scene scene;
    StdRayTracer stdrt;
    scene.addObject(plane);
    scene.addObject(sphere1);
    scene.addSource(lightSource);
    scene.setCamera(camera);

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }

    stdrt.render(scene);
}

int main(int argc, const char **argv) {
    test();
    return 0;
}

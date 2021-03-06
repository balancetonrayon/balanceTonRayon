#include <opencv2/opencv.hpp>

#include "RayTracer.hpp"
#include "Parser.hpp"

#include <fstream>
#include <string>

Scene daltons() {
    Scene scene;
    
    std::ifstream ifs("chemin vers le fichier");
    std::string xmlData((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
    
    Parser parser(xmlData);
    
    std::cout << parser.getName() << std::endl;

    /*auto plane = std::make_shared<Plane>(glm::vec3(0, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 1),
                                         0, 0, 0.2, 0.25);

    auto sphere1 =
        std::make_shared<Sphere>(glm::vec3(6.16, 0.66, 1), glm::vec3(1, 1, 1), 1, 0, 0, 0.8, 0.22);
    auto sphere2 =
        std::make_shared<Sphere>(glm::vec3(5, 0, 0.66), glm::vec3(0, 1, 1), 0.66, 0, 0, 0.2, 0.35);
    auto sphere3 = std::make_shared<Sphere>(glm::vec3(4.16, 0.44, 0.20), glm::vec3(0, 0, 1), 0.20,
                                            0, 0, 0.1, 0.20);
    auto sphere4 = std::make_shared<Sphere>(glm::vec3(5.25, 3, 0.66), glm::vec3(1, 1, 1), 0.25,
                                            0.95, 1.5, 0, 0.05);
    auto camera = std::make_shared<Camera>(glm::vec3(5, 5, 0.66), glm::vec3(0, -1, 0), 0.1, 0.1,
                                           2000, 2000, 0.05);
    auto lightSource =
        std::make_shared<DirectLight>(glm::vec3(5, 2.5, 3), glm::vec3(1, 1, 1), 2000);

    scene.addObject(plane);
    scene.addObject(sphere1);
    scene.addObject(sphere2);
    scene.addObject(sphere3);
    scene.addObject(sphere4);
    scene.setCamera(camera);
    scene.addSource(lightSource);*/
    
    for (auto object : parser.getObjects())
        scene.addObject(object);
    
    for (auto source : parser.getSources())
        scene.addSource(source);
    
    scene.setCamera(parser.getCamera());

    return scene;
}

void test() {
    Scene scene = daltons();
    StdRayTracer stdrt;

    for (auto object : scene.getObjects()) {
        std::cout << *object << std::endl;
    }

    stdrt.render(scene);

    cv::waitKey(0);
}

int main(int argc, const char **argv) {
    test();
    return 0;
}

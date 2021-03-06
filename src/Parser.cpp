#include "Parser.hpp"

#include <string>

Parser::Parser(std::string xmlData) {
    doc.Parse(xmlData.c_str());
    auto scene = doc.FirstChildElement("scene");

    // meta
    auto metaTag = scene->FirstChildElement("meta");
    name = metaTag->FirstChildElement("name")->GetText();
    size = getXY(metaTag->FirstChildElement("size"));
    backgroundColor = getRGB(metaTag->FirstChildElement("background-color"));
    maxDepth = std::stoi(metaTag->FirstChildElement("max_depth")->GetText());

    // camera
    auto cameraTag = scene->FirstChildElement("camera");
    auto cameraPos = getXYZ(cameraTag->FirstChildElement("pos"));
    auto cameraDir = getXYZ(cameraTag->FirstChildElement("dir"));
    auto cameraFoc = std::stof(cameraTag->FirstChildElement("foc")->GetText());
    auto cameraSize = getXY(cameraTag->FirstChildElement("size"));
    auto cameraPix = getXY(cameraTag->FirstChildElement("pix"));
    camera = std::make_shared<Camera>(cameraPos, cameraDir, cameraSize.x, cameraSize.y, cameraPix.x,
                                      cameraPix.y, cameraFoc);

    // lightsources
    auto lightTag = scene->FirstChildElement("lightsources");
    auto dlightTag = lightTag->FirstChildElement("directLight");
    auto dlightPos = getXYZ(dlightTag->FirstChildElement("pos"));
    auto dlightColor = getRGB(dlightTag->FirstChildElement("color"));
    auto dlightIntensity = std::stoi(dlightTag->FirstChildElement("intensity")->GetText());
    sources.push_back(std::make_shared<DirectLight>(dlightPos, dlightColor, dlightIntensity));

    // objects
    auto objectsTag = scene->FirstChildElement("objects");
    for (auto objectTag = objectsTag->FirstChildElement(); objectTag != NULL;
         objectTag = objectTag->NextSiblingElement()) {
        std::string objectName = objectTag->Name();

        // common for all objects
        auto objectPos = getXYZ(objectTag->FirstChildElement("pos"));
        auto objectColor = getRGB(objectTag->FirstChildElement("color"));
        auto objectTransmission =
            std::stof(objectTag->FirstChildElement("transmission")->GetText());
        auto objectReflexion = std::stof(objectTag->FirstChildElement("reflexion")->GetText());
        auto objectRefractive = std::stof(objectTag->FirstChildElement("refractive")->GetText());
        auto objectAlbedo = std::stof(objectTag->FirstChildElement("albedo")->GetText());

        bool foundImage = false;
        bool foundChecked = false;
        std::shared_ptr<Image> image;
        std::shared_ptr<CheckedPattern2D> checked;

        try {
            auto objectTexture = objectTag->FirstChildElement("texture");
            if (objectTexture != NULL &&
                !((std::string)(objectTexture->FirstChildElement()->Name())).compare("image")) {
                auto imageTag = objectTexture->FirstChildElement("image");
                auto filename =
                    "../data/" + (std::string)(imageTag->FirstChildElement("path")->GetText());
                auto origin = getXYZ(imageTag->FirstChildElement("origin"));
                auto wVec = getXYZ(imageTag->FirstChildElement("wVec"));
                auto hVec = getXYZ(imageTag->FirstChildElement("hVec"));
                image = std::make_shared<Image>(filename, origin, hVec, wVec);
                foundImage = true;
            } else if (objectTexture != NULL &&
                       !((std::string)(objectTexture->FirstChildElement()->Name()))
                            .compare("checked-pattern-2d")) {
                auto checkedTag = objectTexture->FirstChildElement("checked-pattern-2d");
                auto color = getRGB(checkedTag->FirstChildElement("color"));
                checked = std::make_shared<CheckedPattern2D>(color);
                foundChecked = true;
            }
        } catch (std::exception exc) {
            -1;  // it doesn't matter
        }

        // object specific
        if (objectName == "plane") {
            auto planeNormal = getXYZ(objectTag->FirstChildElement("normal"));
            auto plane =
                std::make_shared<Plane>(objectPos, planeNormal, objectColor, objectTransmission,
                                        objectRefractive, objectReflexion, objectAlbedo);
            if (foundImage) {
                plane->setTexture(image);
            } else if (foundChecked) {
                plane->setTexture(checked);
            }
            objects.push_back(plane);
        } else if (objectName == "sphere") {
            auto sphereRadius = std::stof(objectTag->FirstChildElement("radius")->GetText());
            auto sphere =
                std::make_shared<Sphere>(objectPos, objectColor, sphereRadius, objectTransmission,
                                         objectRefractive, objectReflexion, objectAlbedo);
            if (foundImage) {
                sphere->setTexture(image);
            } else if (foundChecked) {
                sphere->setTexture(checked);
            }
            objects.push_back(sphere);
        } else if (objectName == "triangle") {
            auto triangleV1 = getXYZ(objectTag->FirstChildElement("v1"));
            auto triangleV2 = getXYZ(objectTag->FirstChildElement("v2"));
            auto triangleNormal = getXYZ(objectTag->FirstChildElement("normal"));
            auto triangle = std::make_shared<Triangle>(
                objectPos, triangleV1, triangleV2, triangleNormal, objectColor, objectTransmission,
                objectRefractive, objectReflexion, objectAlbedo);
            if (foundImage) {
                triangle->setTexture(image);
            } else if (foundChecked) {
                triangle->setTexture(checked);
            }
            objects.push_back(triangle);
        }
    }
}

glm::vec2 Parser::getXY(const tinyxml2::XMLElement* element) {
    float x = std::stof(element->FirstChildElement("x")->GetText());
    float y = std::stof(element->FirstChildElement("y")->GetText());
    return glm::vec2(x, y);
}

glm::vec3 Parser::getXYZ(const tinyxml2::XMLElement* element) {
    float x = std::stof(element->FirstChildElement("x")->GetText());
    float y = std::stof(element->FirstChildElement("y")->GetText());
    float z = std::stof(element->FirstChildElement("z")->GetText());
    return glm::vec3(x, y, z);
}

glm::vec3 Parser::getRGB(const tinyxml2::XMLElement* element) {
    float r = std::stof(element->FirstChildElement("r")->GetText());
    float g = std::stof(element->FirstChildElement("g")->GetText());
    float b = std::stof(element->FirstChildElement("b")->GetText());
    return glm::vec3(r, g, b);
}

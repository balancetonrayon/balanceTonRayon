#pragma once

#include "Object.hpp"

#include <string>
#include <tinyxml2.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class Parser {
    tinyxml2::XMLDocument doc;
    
    std::string name;
    glm::vec2 size;
    int maxDepth;
    
    std::vector<std::shared_ptr<BasicObject>> objects;
    
    std::vector<std::shared_ptr<Light>> sources;
    
    std::shared_ptr<Camera> camera;
    
public:
    Parser() = delete;
    Parser(std::string xmlData);
    
    std::string getName() const { return name; }
    glm::vec2 getSize() const { return size; }
    int getMaxDepth() const { return maxDepth; }
    
    const std::vector<std::shared_ptr<BasicObject>> & getObjects() const { return objects; }
    const std::vector<std::shared_ptr<Light>> & getSources() const { return sources; }
    const std::shared_ptr<Camera> & getCamera() const { return camera; }
    
private:
    glm::vec2 getXY(const tinyxml2::XMLElement* element);
    glm::vec3 getXYZ(const tinyxml2::XMLElement* element);
    glm::vec3 getRGB(const tinyxml2::XMLElement* element);
};

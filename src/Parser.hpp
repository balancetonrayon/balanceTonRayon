/**
 * @file Parser.hpp
 * @author Atoli Huppé & Olivier Laurent
 * @brief Parses XML to retrieve data about a scene.
 * @version 1.0
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <string>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <tinyxml2.h>

#include "Object/Camera.hpp"
#include "Object/BasicObject.hpp"
#include "Object/DirectLight.hpp"

/**
 * @class Parser
 * @brief Parses XML for scene generation.
 *
 */
class Parser {
    tinyxml2::XMLDocument doc;

    std::string name;
    glm::vec2 size;
    int maxDepth;
    glm::vec3 backgroundColor;
    std::vector<std::shared_ptr<BasicObject>> objects;

    std::vector<std::shared_ptr<Light>> sources;

    std::shared_ptr<Camera> camera;

public:
    Parser() = delete;
    Parser(std::string xmlData);

    std::string getName() const { return name; }
    glm::vec2 getSize() const { return size; }
    int getMaxDepth() const { return maxDepth; }
    glm::vec3 getBackgroundColor() const { return backgroundColor; }

    const std::vector<std::shared_ptr<BasicObject>>& getObjects() const { return objects; }
    const std::vector<std::shared_ptr<Light>>& getSources() const { return sources; }
    const std::shared_ptr<Camera>& getCamera() const { return camera; }

private:
     /**
     * @brief Fetch data from an XML element containing x, y elements.
     *
     * @param The element where the xy data lies.
     * @return glm::vec2
     */

    glm::vec2 getXY(const tinyxml2::XMLElement* element);

    /**
     * @brief Fetch data from an XML element containing x, y and z elements.
     *
     * @param The element where the xyz data lies.
     * @return glm::vec3
     */
    glm::vec3 getXYZ(const tinyxml2::XMLElement* element);

     /**
     * @brief Fetch data from an XML element containing r, g and b elements.
     *
     * @param The element where the rgb data lies.
     * @return glm::vec3
     */

    glm::vec3 getRGB(const tinyxml2::XMLElement* element);
};

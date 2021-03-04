#include <exception>
#include <fstream>
#include <iostream>

#include "Object.hpp"

class ObjParser {
public:
    ObjParser(){};

    //! A normal member taking one argument and returning a mesh.
    /*!
      \param filename the name of the .obj file
      \return The information of the object as an ostream
      Raises runtime error if the obj file is not well formated
    */
    PolygonMesh readObj(std::string filename) noexcept(false) {
        std::cout << filename << std::endl;
        std::vector<glm::vec3> v;
        std::vector<glm::vec2> vt;
        std::vector<glm::vec3> vn;

        PolygonMesh mesh;

        std::ifstream objFile(filename);

        if (objFile.is_open()) {
            float v1 = 0;
            float v2 = 0;
            float v3 = 0;
            std::string type;

            // Get the vertices
            objFile >> type;
            while (type == "v") {
                objFile >> v1;
                objFile >> v2;
                objFile >> v3;
                objFile >> type;
                v.push_back(glm::vec3(v1, v2, v3));
            }
            std::cout << v.size() << std::endl;

            bool texture3D = false;
            // Get the texture
            while (type == "vt") {
                objFile >> v1;
                objFile >> v2;
                if (texture3D || objFile.peek() != '\n') {
                    texture3D = true;
                    objFile >> v3;
                } else {
                    v3 = 0;
                }
                vt.push_back(glm::vec3(v1, v2, v3));
                objFile >> type;
            }
            std::cout << vt.size() << std::endl;
            // Get the normals
            while (type == "vn") {
                objFile >> v1;
                objFile >> v2;
                objFile >> v3;
                vn.push_back(glm::vec3(v1, v2, v3));
                objFile >> type;
            }
            std::cout << vn.size() << std::endl;
            // Faces
            int c1;
            char c2;
            int c3;
            char c4;
            int c5;

            std::vector<int> c1Vect;
            std::vector<int> c3Vect;
            std::vector<int> c5Vect;

            while (type == "f") {
                c1Vect.clear();
                c3Vect.clear();
                c5Vect.clear();

                // Tant que l'on est pas au bout de la ligne on ajoute des sommets
                while (objFile.peek() != '\n' && !objFile.eof()) {
                    objFile >> c1;
                    objFile >> c2;
                    objFile >> c3;
                    objFile >> c4;
                    objFile >> c5;
                    if (c2 != '/' || c4 != '/')
                        throw std::runtime_error("Error in the obj file format");

                    c1Vect.push_back(c1);
                    c3Vect.push_back(c3);
                    c5Vect.push_back(c5);
                    std::cout << c1 << " " << c3 << " " << c5 << std::endl;
                }
                Polygon poly;
                for (int k = 0; k < c1Vect.size(); ++k) {
                    poly.addVertice(v[c1Vect[k] - 1]);  // Les indices de l'obj commencent à 1
                    poly.addTexture(vt[c3Vect[k] - 1]);
                }
                std::cout << vn[c5Vect[0]] << std::endl;
                poly.setNormal(vn[c5Vect[0]]);
                std::cout << poly.normal << std::endl;
                mesh.addPolygon(poly);

                if (objFile.eof()) break;
                objFile >> type;
            }
            return mesh;
        } else {
            std::cout << "Error in filename";
            return mesh;
        }
    }
};
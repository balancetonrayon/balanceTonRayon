#include "Object.hpp"
#include "utils.hpp"

std::ostream &LightSource::printInfo(std::ostream &os) const
{
    return os << "LightSource: in " << pos << ", of color: " << color;
}

Ray Camera::genRay(unsigned x, unsigned y)
{
    //EXCEPTION A AJOUTER
    // Z is the altitude : - X of the image
    glm::vec3 dir(focalLength, (-0.5 + ((float)y) / resY) * sizeY, (0.5 - ((float)x) / resX) * sizeX);
    return Ray(pos, dir);
};

std::ostream &Camera::printInfo(std::ostream &os) const
{
    return os << "Camera: in " << pos << ", of size: " << sizeX;
}

std::vector<Ray> Plane::intersect(const Ray ray, const LightSource ltSrc)
{
    std::vector<Ray> rays;
    // Calcul du point d'intersection
    float distance;
    bool inter = glm::intersectRayPlane(ray.initPt, ray.dir, pos, normal, distance);
    if (inter)
    {
        std::cout << "Distance à l'intersection: " << distance << std::endl;
        glm::vec3 intersectPt = distance * ray.initPt;
        glm::vec3 dir = glm::normalize(-intersectPt + ltSrc.pos);

        // Si la source n'est pas derrière le plan, on ajoute le rayon réfléchi
        std::cout << glm::dot(dir, normal) << std::endl;
        if (glm::dot(dir, normal) > 0)
        {
            rays.push_back(Ray(intersectPt, dir));
        }
    }
    std::cout << rays.size() << std::endl;
    return rays;
}

std::ostream &Plane::printInfo(std::ostream &os) const
{
    return os << "Plane: in " << pos << ", of normal " << normal;
}

std::vector<Ray> Sphere::intersect(const Ray ray, const LightSource ltSrc)
{
    std::vector<Ray> rays;

    glm::vec3 intersectPt;
    glm::vec3 normal;
    bool inter = glm::intersectRaySphere(ray.initPt, ray.dir, pos, radius, intersectPt, normal);

    glm::vec3 dir = glm::normalize(intersectPt - ltSrc.pos);

    // Si la source n'est pas derrière la sphère, on ajoute le rayon réfléchi
    if (glm::dot(dir, normal) > 0)
    {
        rays.push_back(Ray(intersectPt, dir));
    }
    return rays;
}

std::ostream &Sphere::printInfo(std::ostream &os) const
{
    return os << "Sphere: in " << pos << ", of radius: " << radius;
}

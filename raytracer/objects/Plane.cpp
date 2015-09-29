#include "Plane.h"

double Plane::intersect(const Ray* ray) const {
    return false;
}

glm::vec3 Plane::getNormal(const glm::vec4& point) const {
    return normal;
}

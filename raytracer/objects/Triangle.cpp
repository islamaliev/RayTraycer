#include <vector>
#include "Triangle.h"
#include "Ray.h"

Triangle::Triangle(const glm::mat4& m, const vec3* v1, const vec3* v2, const vec3* v3)
    : Object(m) {
    verticies.push_back(v1);
    verticies.push_back(v2);
    verticies.push_back(v3);

    const vec3& side1(*verticies[1] - *verticies[0]);
    const vec3& side2(*verticies[2] - *verticies[0]);
    localNormal = vec4(glm::normalize(glm::cross(side1, side2)), 0);

    const vec3& transformedNormal = vec3(glm::transpose(getInverseTransform()) * localNormal);
    normal = glm::normalize(transformedNormal);
}

double Triangle::intersect(const Ray* ray) const {
    const mat4& invM = getInverseTransform();

    vec4 localRayPos = invM * ray->pos;
    vec4 localRayDir = invM * ray->dir;

    double d = glm::dot(localRayDir, localNormal);
    if (d == 0) {
        return 0;
    }

    vec4 a(*verticies[0], 0);

    double t = (glm::dot(a, localNormal) - glm::dot(localRayPos, localNormal)) / d;
    if (t < 0) {
        return 0;
    }

    vec4 p(localRayPos + (localRayDir * t));
    if (isPointInTriangle(vec3(p), *verticies[0], *verticies[2], *verticies[1]))
    {
        p = ray->pos - getTransform() * p;
        return glm::length(p);
    }

    return 0;
}

bool Triangle::isPointInTriangle(const vec3& p, const vec3& a, const vec3& b, const vec3& c) const {
    vec3 v0 = c - a;
    vec3 v1 = b - a;
    vec3 v2 = p - a;

    double dot00 = glm::dot(v0, v0);
    double dot01 = glm::dot(v0, v1);
    double dot02 = glm::dot(v0, v2);
    double dot11 = glm::dot(v1, v1);
    double dot12 = glm::dot(v1, v2);

    double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

glm::vec3 Triangle::getNormal(const glm::vec4& point) const {
    return normal;
}
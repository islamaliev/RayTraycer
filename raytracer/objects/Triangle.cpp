#include <vector>
#include "Triangle.h"
#include "Ray.h"

Triangle::Triangle(const vec3* v1, const vec3* v2, const vec3* v3) {
    verticies.push_back(v1);
    verticies.push_back(v2);
    verticies.push_back(v3);
}

float Triangle::intersect(const Ray* ray) const {
    mat4 invM = getInverseTransform();

    vec4 rayPos = invM * ray->pos;
    vec4 rayDir = invM * ray->dir;

    const vec3& side1(*verticies[1] - *verticies[0]);
    const vec3& side2(*verticies[2] - *verticies[0]);
    vec4 n = glm::normalize(vec4(glm::cross(side1, side2), 0));

    float d = glm::dot(rayDir, n);
    if (d == 0) {
        return 0;
    }

    vec4 a(*verticies[0], 0);

    float t = (glm::dot(a, n) - glm::dot(rayPos, n)) / d;
    if (t < 0) {
        return 0;
    }

    vec4 p = rayPos + (rayDir * t);
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

    float dot00 = glm::dot(v0, v0);
    float dot01 = glm::dot(v0, v1);
    float dot02 = glm::dot(v0, v2);
    float dot11 = glm::dot(v1, v1);
    float dot12 = glm::dot(v1, v2);

    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v < 1);
}

glm::vec3 Triangle::getNormal(glm::vec4 point)
{
    const vec3& side1(*verticies[1] - *verticies[0]);
    const vec3& side2(*verticies[2] - *verticies[0]);
    return glm::normalize(glm::cross(side1, side2));
}

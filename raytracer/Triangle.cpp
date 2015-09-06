#include <vector>
#include "Triangle.h"
#include "Ray.h"

Triangle::Triangle(const vec3* v1, const vec3* v2, const vec3* v3) {
    verticies.push_back(v1);
    verticies.push_back(v2);
    verticies.push_back(v3);
}

float Triangle::intersect(Ray* ray) {
    const vec3& side1 = *verticies[2] - *verticies[0];
    const vec3& side2 = *verticies[1] - *verticies[0];
    vec3 n = glm::normalize(glm::cross(side1, side2));

    float d = glm::dot(ray->dir, n);
    if (d == 0) {
        return 0;
    }

    const vec3& a = *verticies[0];
    float t = (glm::dot(a, n) - glm::dot(ray->pos, n)) / d;

    vec3 p = ray->pos + ray->dir * t;
    if (isPointInTriangle(p, *verticies[0], *verticies[1], *verticies[2])) {
        return t;
    }

    return 0;
}

bool Triangle::isOnSameSide(const vec3& p1, const vec3& p2, const vec3& a, const vec3& b) {
    vec3 cp1 = glm::cross(b - a, p1 - a);
    vec3 cp2 = glm::cross(b - a, p2 - a);
    return glm::dot(cp1, cp2) >= 0;
}

bool Triangle::isPointInTriangle(const vec3& p, const vec3& a, const vec3& b, const vec3& c) {
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


//    return isOnSameSide(p, a, b, c) && isOnSameSide(p, b, a, c) && isOnSameSide(p, c, a, b);
}
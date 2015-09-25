#include "Sphere.h"
#include "Ray.h"

double Sphere::intersect(const Ray* ray) const {
    // a * t ^ 2 + b * t + c = 0
    // t ^ 2 * (P1 * P1) + 2 * t * P1 * (P0 - C) + (P0 - C) * (P0 - C) - r ^ 2 = 0
    // a = P1 * P1
    // b = 2 * P1 * (P0 - C)
    // c = (P0 - C) * (P0 - C) - r ^ 2
    // D = b ^ 2 - 4 * a * c
    const mat4& invM = getInverseTransform();

    vec4 rayPos = invM * ray->pos;
    vec4 rayDir = invM * ray->dir;

    glm::vec4 diff = rayPos - position;
    double a = glm::dot(rayDir, rayDir);
    double b = 2 * glm::dot(rayDir, diff);
    double c = glm::dot(diff, diff) - pow(radius, 2);
    double D = pow(b, 2) - 4 * a * c;
    if (D < 0) {
        return 0;
    }
    if (D == 0) {
        return -b / (2 * a);
    }
    double sqD = sqrt(D);
    double t1 = -(b + sqD) / (2 * a);
    double t2 = (sqD - b) / (2 * a);

    if (t1 < 0 && t2 < 0) {
        return 0;
    }

    double t;
    if (t1 < 0) {
        t = t2;
    } else if (t2 < 0) {
        t = t1;
    } else {
        t = t1 < t2 ? t1 : t2;
    }

    vec4 p = rayPos + (rayDir * t);
    p = ray->pos - getTransform() * p;
    return glm::length(p);
}

glm::vec3 Sphere::getNormal(const glm::vec4& point) const {
    const mat4& inv = getInverseTransform();
    vec4 objPoint = inv * point;
    vec3 normDir = glm::normalize(vec3(objPoint - position));
    vec3 normDir3 = vec3(glm::transpose(inv) * vec4(normDir, 0));
    return glm::normalize(normDir3);
}

#include "Sphere.h"
#include "Ray.h"

float Sphere::intersect(Ray* ray) {
    // a * t ^ 2 + b * t + c = 0
    // t ^ 2 * (P1 * P1) + 2 * t * P1 * (P0 - C) + (P0 - C) * (P0 - C) - r ^ 2 = 0
    // a = P1 * P1
    // b = 2 * P1 * (P0 - C)
    // c = (P0 - C) * (P0 - C) - r ^ 2
    // D = b ^ 2 - 4 * a * c
    glm::vec3 diff = ray->pos - position;
    float a = glm::dot(ray->dir, ray->dir);
    float b = 2 * glm::dot(ray->dir, diff);
    float c = glm::dot(diff, diff) - powf(radius, 2);
    float D = powf(b, 2) - 4 * a * c;
    if (D < 0) {
        return 0;
    }
    if (D == 0) {
        return -b / (2 * a);
    }
    float sqD = sqrtf(D);
    float t1 = (-b - sqD) / (2 * a);
    float t2 = (-b + sqD) / (2 * a);

    return t1 < t2 ? t1 : t2;
}
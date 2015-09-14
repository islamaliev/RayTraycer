#include "ReflectionTracer.h"
#include "Intersection.h"
#include "Ray.h"
#include "IntersectionDetector.h"
#include "ColorCalculator.h"

glm::vec3 ReflectionTracer::findColor(const Intersection* const intersection, const glm::vec3& normal, unsigned depth) const {
    const vec3& l = -vec3(intersection->ray->dir);
    float nDot = glm::dot(l, normal);
    vec3 doubleNormal = normal * nDot * 2.f;

    Ray* ray = new Ray();
    ray->dir = glm::vec4(doubleNormal - l, 0);
    ray->pos = intersection->ray->pos + intersection->ray->dir * intersection->dist + ray->dir * 0.001f;
    Intersection* reflectedIntersection = intersectionDetector->getIntersection(ray);
    unsigned reflectedColor = colorCalculator->calculate(reflectedIntersection , depth);
    unsigned char mask = 0xFF;
    float b = reflectedColor & mask;
    b /= (float) mask;
    float g = reflectedColor >> 8 & mask;
    g /= (float) mask;
    float r = reflectedColor >> 19 & mask;
    r /= (float) mask;
    return vec3(r, g , b);
}

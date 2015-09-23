#include "ReflectionTracer.h"
#include "Intersection.h"
#include "Ray.h"
#include "IntersectionDetector.h"
#include "ColorCalculator.h"
#include "Scene.h"

unsigned ReflectionTracer::findColor(const Intersection* const intersection, const glm::vec3& normal, unsigned depth) const {
    if (++depth > scene->maxDepth) {
        return 0;
    }
    const vec3& l = -vec3(intersection->ray->dir);
    float nDot = glm::dot(l, normal);
    vec3 doubleNormal = normal * nDot * 2.f;

    Ray* ray = new Ray();
    ray->dir = glm::vec4(doubleNormal - l, 0);
    ray->pos = intersection->ray->pos + intersection->ray->dir * intersection->dist + ray->dir * 0.001f;
    Intersection* reflectedIntersection = intersectionDetector->getIntersection(ray);
    return colorCalculator->calculate(reflectedIntersection , depth);
}

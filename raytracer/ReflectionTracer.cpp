#include "ReflectionTracer.h"
#include "Intersection.h"
#include "IntersectionDetector.h"
#include "ColorCalculator.h"
#include "Scene.h"
#include "RayGenerator.h"
#include "Color.h"

Color ReflectionTracer::findColor(const Intersection* const intersection, const glm::vec3& normal, unsigned depth) const {
    if (++depth > scene->maxDepth) {
        return Color();
    }
    const vec3& l = -vec3(intersection->ray->dir);
    double nDot(glm::dot(l, normal));
    const vec3& doubleNormal = normal * nDot * 2.0;

    Ray* ray = RayGenerator().generate(intersection->point, doubleNormal - l);

    Intersection* reflectedIntersection = intersectionDetector->getIntersection(ray);
    return colorCalculator->calculate(reflectedIntersection , depth);
}

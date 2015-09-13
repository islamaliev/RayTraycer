#include <vector>
#include "IntersectionDetector.h"
#include "Object.h"
#include "Scene.h"
#include "Intersection.h"

Intersection* IntersectionDetector::getIntersection(Ray* ray) const {
    float minDist = 0;
    float currentDist;
    Object* hitObject = nullptr;
    std::vector<Object*>& objects = scene->objects;
    for (auto it = objects.begin(); it != objects.end(); it++) {
        currentDist = intersect(ray, *it);
        if (currentDist > 0 && (currentDist < minDist || minDist == 0)) {
            minDist = currentDist;
            hitObject = *it;
        }
    }
    return new Intersection(minDist, ray, hitObject);
}

float IntersectionDetector::intersect(const Ray* ray, const Object* object) const {
    return object->intersect(ray);
}

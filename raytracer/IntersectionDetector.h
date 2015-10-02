#pragma once


class Intersection;
class Ray;
class Scene;
class Object;

class IntersectionDetector {
public:
    IntersectionDetector(Scene* scene)
        : scene(scene) {}

    Intersection* getIntersection(Ray* ray) const;

private:
    double intersect(const Ray* ray, const Object* object) const;

    Scene* scene;
};

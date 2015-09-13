#ifndef HW3_INTERSECTIONDETECTOR_H
#define HW3_INTERSECTIONDETECTOR_H


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
    float intersect(const Ray* ray, const Object* object) const;

    Scene* scene;
};


#endif //HW3_INTERSECTIONDETECTOR_H

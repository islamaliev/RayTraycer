#pragma once


#include "glm/glm.hpp"

class Scene;
class Intersection;
class IntersectionDetector;
class ColorCalculator;
class Color;

class ReflectionTracer {
public:
    ReflectionTracer(Scene* scene, IntersectionDetector* intersectionDetector, ColorCalculator* colorCalculator)
        : scene(scene)
        , intersectionDetector(intersectionDetector)
        , colorCalculator(colorCalculator) {
    }

    Color findColor(const Intersection* const intersection, const glm::vec3& normal, unsigned depth = 0) const;

private:
    typedef glm::vec3 vec3;

    Scene* scene;
    IntersectionDetector* intersectionDetector;
    ColorCalculator* colorCalculator;
};

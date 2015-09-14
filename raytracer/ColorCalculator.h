#ifndef HW3_COLORCALCULATOR_H
#define HW3_COLORCALCULATOR_H


#include "glm/glm.hpp"
#include "ReflectionTracer.h"

class Intersection;
class Scene;
class IntersectionDetector;
class Light;

class ColorCalculator {
public:
    ColorCalculator(Scene* const scene, IntersectionDetector* intersectionDetector)
        : scene(scene)
        , intersectionDetector(intersectionDetector)
        , reflectionTracer(scene, intersectionDetector, this) {
    }

    unsigned calculate(const Intersection* intersection, unsigned depth = 0) const;

private:
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;

    unsigned convertToInt(const glm::vec3& color) const;

    vec3 computeLight(const vec3& direction, const vec3& lightColor, const vec3& normal, const vec3& half,
            const vec3& diffuse, const vec3& specular, float shininess) const;

    bool isLit(const glm::vec4& point, Light* light) const;

    Scene* const scene;
    IntersectionDetector* const intersectionDetector;
    ReflectionTracer reflectionTracer;
};


#endif //HW3_COLORCALCULATOR_H

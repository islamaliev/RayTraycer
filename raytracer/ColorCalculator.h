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

    ~ColorCalculator() {
        scene = nullptr;
        intersectionDetector = nullptr;
    }

    unsigned calculate(const Intersection* intersection, unsigned depth = 0) const;

private:
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;

    unsigned convertToInt(const glm::vec3& color) const;
    glm::vec3 convertToVec(unsigned color) const;

    glm::vec3 computeLight(const vec3& direction, const vec3& lightColor, const vec3& normal, const vec3& half,
            const vec3& diffuse, const vec3& specular, float shininess) const;

    bool isLit(const glm::vec4& point, Light* light, glm::vec3& lightDir, double& lightDistance) const;

    const Scene* scene;
    const IntersectionDetector* intersectionDetector;
    ReflectionTracer reflectionTracer;
};


#endif //HW3_COLORCALCULATOR_H

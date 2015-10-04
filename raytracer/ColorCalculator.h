#pragma once


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

    void contributeLight(glm::vec3& color, const Light* light, const Intersection* intersection, const glm::vec3& normal) const;

    void contributeReflection(glm::vec3& color, const Intersection* intersection, const glm::vec3& normal, unsigned depth) const;

    bool isLit(const glm::vec4& point, const Light* light, const glm::vec3& lightDir, const double& lightDistance) const;

    const Scene* scene;
    const IntersectionDetector* intersectionDetector;
    ReflectionTracer reflectionTracer;
};

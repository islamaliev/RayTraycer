#pragma once


#include "glm/glm.hpp"
#include "ReflectionTracer.h"

class Intersection;
class Scene;
class IntersectionDetector;
class Light;
class Color;

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

    Color calculate(const Intersection* intersection, unsigned depth = 0) const;

private:
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;

    Color computeLight(const vec3& direction, const Color& lightColor, const vec3& normal, const vec3& half,
            const Color& diffuse, const Color& specular, float shininess) const;

    void contributeLight(Color& color, const Light* light, const Intersection* intersection, const glm::vec3& normal) const;

    void contributeReflection(Color& color, const Intersection* intersection, const glm::vec3& normal, unsigned depth) const;

    bool isLit(const glm::vec4& point, const Light* light, const glm::vec3& lightDir, const double& lightDistance) const;

    const Scene* scene;
    const IntersectionDetector* intersectionDetector;
    ReflectionTracer reflectionTracer;
};

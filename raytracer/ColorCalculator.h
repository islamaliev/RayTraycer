#ifndef HW3_COLORCALCULATOR_H
#define HW3_COLORCALCULATOR_H


#include "glm/glm.hpp"

class Intersection;
class Scene;
class IntersectionDetector;
class Light;

class ColorCalculator {
public:
    ColorCalculator(Scene* const scene, IntersectionDetector* intersectionDetector)
        : scene(scene)
        , intersectionDetector(intersectionDetector) {
    }

    unsigned calculate(const Intersection* intersection) const;

private:
    typedef glm::vec3 vec3;

    unsigned convertToInt(const glm::vec3& color) const;

    vec3 computeLight(const vec3& direction, const vec3& lightColor, const vec3& normal, const vec3& half,
            const vec3& diffuse, const vec3& specular, float shininess) const;

    bool isLit(const glm::vec4& point, Light* light) const;

    Scene* const scene;
    IntersectionDetector* const intersectionDetector;
};


#endif //HW3_COLORCALCULATOR_H

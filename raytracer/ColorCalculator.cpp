#include "ColorCalculator.h"
#include "Intersection.h"
#include "Scene.h"
#include "Light.h"
#include "Object.h"
#include "Camera.h"
#include "IntersectionDetector.h"
#include "RayGenerator.h"

glm::vec3 ColorCalculator::computeLight(const vec3& direction, const vec3& lightColor, const vec3& normal, const vec3& half,
        const vec3& diffuse, const vec3& specular, float shininess) const {
    double nDotL = glm::dot(normal, direction);
    if (nDotL < 0) {
        nDotL = 0;
    }
    vec3 lambert = diffuse * lightColor * nDotL;

    double nDotH = glm::dot(normal, half);
    if (nDotH < 0) {
        nDotH = 0;
    }
    vec3 phong = specular * lightColor * pow(nDotH, shininess);

    return lambert + phong;
}

void ColorCalculator::contributeLight(glm::vec3& color, const Light* light, const Intersection* intersection, const glm::vec3& normal) const {
    const Object* obj = intersection->object;
    vec3 lightDir(light->getDirectionTo(intersection->point));
    double lightDistance(light->getDistanceTo(intersection->point));

    if (isLit(intersection->point, light, lightDir, lightDistance)) {
        vec3 eye(-vec3(intersection->ray->dir));
        vec3 half(glm::normalize(lightDir + eye));
        vec3 lightColor(computeLight(lightDir, light->color, normal, half, obj->diffuse, obj->specular, obj->shininess));

        color += lightColor / light->getFalloffAt(lightDistance);
    }
}

unsigned ColorCalculator::calculate(const Intersection* intersection, unsigned depth) const {
    if (intersection->dist <= 0) {
        delete intersection;
        return 0;
    }

    const Object* obj = intersection->object;
    vec3 finalColor = obj->ambient + obj->emission;

    const vec3& normal = obj->getNormal(intersection->point);

    for (auto it = scene->lights.begin(); it != scene->lights.end(); it++) {
        contributeLight(finalColor, *it, intersection, normal);
    }

    contributeReflection(finalColor, intersection, normal, depth);

    delete intersection;

    if (finalColor.r > 1) finalColor.r = 1;
    if (finalColor.g > 1) finalColor.g = 1;
    if (finalColor.b > 1) finalColor.b = 1;
    return convertToInt(finalColor);
}

void ColorCalculator::contributeReflection(glm::vec3& color, const Intersection* intersection, const glm::vec3& normal, unsigned depth) const {
    unsigned reflectedColor = reflectionTracer.findColor(intersection, normal, depth);
    if (reflectedColor != 0) {
        color += convertToVec(reflectedColor) * intersection->object->specular;
    }
}

glm::vec3 ColorCalculator::convertToVec(unsigned color) const {
    unsigned char mask = 0xFF;
    float b = color & mask;
    b /= (float) mask;
    float g = color >> 8 & mask;
    g /= (float) mask;
    float r = color >> 16 & mask;
    r /= (float) mask;
    return glm::vec3(r, g , b);
}

unsigned ColorCalculator::convertToInt(const glm::vec3& color) const {
    unsigned char mask = 0xFF;
    unsigned char r = (unsigned char) (color.r * mask);
    unsigned char g = (unsigned char) (color.g * mask);
    unsigned char b = (unsigned char) (color.b * mask);
    unsigned result(b);
    result |= r << 16;
    result |= g << 8;
    return result;
}

bool ColorCalculator::isLit(const glm::vec4& point, const Light* light, const glm::vec3& lightDir, const double& lightDistance) const {
    Ray* ray = RayGenerator().generate(point, lightDir);
    Intersection* lightIntersection = intersectionDetector->getIntersection(ray);
    const double& distToIntersection = lightIntersection->dist;
    delete lightIntersection;
    return light->isCloserTo(point, distToIntersection, lightDistance);
}

#include "ColorCalculator.h"
#include "Intersection.h"
#include "Scene.h"
#include "Light.h"
#include "Object.h"
#include "Camera.h"
#include "IntersectionDetector.h"
#include "RayGenerator.h"

Color ColorCalculator::computeLight(const vec3& direction, const Color& lightColor, const vec3& normal, const vec3& half,
        const Color& diffuse, const Color& specular, float shininess) const {
    double nDotL = glm::dot(normal, direction);
    if (nDotL < 0) {
        nDotL = 0;
    }
    Color lambert(diffuse * lightColor * nDotL);

    double nDotH = glm::dot(normal, half);
    if (nDotH < 0) {
        nDotH = 0;
    }
    Color phong(specular * lightColor * pow(nDotH, shininess));

    return lambert + phong;
}

void ColorCalculator::contributeLight(Color& color, const Light* light, const Intersection* intersection, const glm::vec3& normal) const {
    const Object* obj = intersection->object;
    vec3 lightDir(light->getDirectionTo(intersection->point));
    double lightDistance(light->getDistanceTo(intersection->point));

    if (isLit(intersection->point, light, lightDir, lightDistance)) {
        vec3 eye(-vec3(intersection->ray->dir));
        vec3 half(glm::normalize(lightDir + eye));
        Color lightColor(computeLight(lightDir, light->color, normal, half, obj->diffuse, obj->specular, obj->shininess));

        color += lightColor / light->getFalloffAt(lightDistance);
    }
}

Color ColorCalculator::calculate(const Intersection* intersection, unsigned depth) const {
    if (intersection->dist <= 0) {
        delete intersection;
        return 0;
    }

    const Object* obj = intersection->object;
    Color finalColor(obj->ambient + obj->emission);

    const vec3& normal = obj->getNormal(intersection->point);

    for (auto it = scene->lights.begin(); it != scene->lights.end(); it++) {
        contributeLight(finalColor, *it, intersection, normal);
    }

    contributeReflection(finalColor, intersection, normal, depth);

    delete intersection;

    finalColor.clamp();
    return finalColor;
}

void ColorCalculator::contributeReflection(Color& color, const Intersection* intersection, const glm::vec3& normal, unsigned depth) const {
    const Color& reflectedColor = reflectionTracer.findColor(intersection, normal, depth);
    color += reflectedColor * intersection->object->specular;
}

bool ColorCalculator::isLit(const glm::vec4& point, const Light* light, const glm::vec3& lightDir, const double& lightDistance) const {
    Ray* ray = RayGenerator().generate(point, lightDir);
    Intersection* lightIntersection = intersectionDetector->getIntersection(ray);
    const double& distToIntersection = lightIntersection->dist;
    delete lightIntersection;
    return light->isCloserTo(point, distToIntersection, lightDistance);
}

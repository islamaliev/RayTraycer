#include "ColorCalculator.h"
#include "Intersection.h"
#include "Scene.h"
#include "Ray.h"
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

unsigned ColorCalculator::calculate(const Intersection* intersection, unsigned depth) const {
    if (intersection->dist <= 0) {
        delete intersection;
        return 0;
    }

    const Object* obj = intersection->object;
    vec3 finalcolor = obj->ambient + obj->emission;

    const vec3& normal = obj->getNormal(intersection->point);

    vec3 lightDir;
    double lightDistance;
    for (auto it = scene->lights.begin(); it != scene->lights.end(); it++) {
        Light* light = *it;

        if (isLit(intersection->point, light, lightDir, lightDistance)) {
            vec3 eye = -vec3(intersection->ray->dir);
            vec3 half = glm::normalize(lightDir + eye);
            vec3 lightColor = computeLight(lightDir, light->color, normal, half, obj->diffuse, obj->specular, obj->shininess);
            if (light->position.w == 1) {
                const double* att = scene->attenuation;
                double attenuation(att[0] + att[1] * lightDistance + att[2] * lightDistance * lightDistance);
                lightColor /= attenuation;
            }
            finalcolor += lightColor;
        }

    }
    unsigned reflectedColor = reflectionTracer.findColor(intersection, normal, depth);
    if (reflectedColor != 0) {
        finalcolor += convertToVec(reflectedColor) * obj->specular;
    }

    delete intersection;

    if (finalcolor.r > 1) finalcolor.r = 1;
    if (finalcolor.g > 1) finalcolor.g = 1;
    if (finalcolor.b > 1) finalcolor.b = 1;
    return convertToInt(finalcolor);
}

glm::vec3 ColorCalculator::convertToVec(unsigned color) const {
    unsigned char mask = 0xFF;
    float b = color & mask;
    b /= (float) mask;
    float g = color >> 8 & mask;
    g /= (float) mask;
    float r = color >> 16 & mask;
    r /= (float) mask;
    return vec3(r, g , b);
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

bool ColorCalculator::isLit(const glm::vec4& point, Light* light, glm::vec3& lightDir, double& lightDistance) const {
    if (light->position.w == 0) {
        lightDir = vec3(light->position);
    } else {
        lightDir = glm::normalize(vec3(light->position - point));
    }

    Ray* ray = RayGenerator().generate(point, lightDir);

    Intersection* lightIntersection = intersectionDetector->getIntersection(ray);
    const double& distToIntersection = lightIntersection->dist;
    bool returnValue(true);
    if (light->position.w == 1) {
        lightDistance = glm::length(vec3(light->position - point));
        if (distToIntersection != 0 && distToIntersection < lightDistance) {
            returnValue = false;
        }
    } else if (distToIntersection > 0) {
        returnValue = false;
    }
    delete lightIntersection;
    return returnValue;
}

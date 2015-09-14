#include "ColorCalculator.h"
#include "Intersection.h"
#include "Scene.h"
#include "Ray.h"
#include "Light.h"
#include "Object.h"
#include "Camera.h"
#include "IntersectionDetector.h"

vec3 ColorCalculator::computeLight(const vec3& direction, const vec3& lightColor, const vec3& normal, const vec3& half,
        const vec3& diffuse, const vec3& specular, float shininess) const {
    float nDotL = glm::dot(normal, direction);
    if (nDotL < 0) {
        nDotL = 0;
    }
    vec3 lambert = diffuse * lightColor * nDotL;

    float nDotH = glm::dot(normal, half);
    if (nDotH < 0) {
        nDotH = 0;
    }
    vec3 phong = specular * lightColor * powf(nDotH, shininess);

    vec3 retval = lambert + phong;
    return retval;
}

unsigned ColorCalculator::calculate(const Intersection* intersection, unsigned depth) const
{
    if (intersection->dist <= 0) {
        return 0;
    }

    vec3 finalcolor;
    Object* obj = intersection->object;

    for (auto it = scene->lights.begin(); it != scene->lights.end(); it++) {
        Light* light = *it;

        vec4 intersectionPoint = intersection->ray->pos + (intersection->ray->dir * intersection->dist);
        vec3 l;
        if (light->position.w == 0) {
            l = vec3(light->position);
        } else {
            l = glm::normalize(vec3(light->position - intersectionPoint));
        }

        finalcolor += obj->ambient + obj->emission;

        vec3 normal = obj->getNormal(intersectionPoint);

        if (isLit(intersectionPoint, light)) {
            vec3 eye = glm::normalize(scene->camera->pos);
            vec3 half = glm::normalize(l + eye);
            finalcolor += computeLight(l, light->color, normal, half, obj->diffuse, obj->specular, obj->shininess);
        }

        if (++depth <= 1) {
            finalcolor += reflectionTracer.findColor(intersection, normal, depth) * obj->specular;
        }
    }
    return convertToInt(finalcolor);
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

bool ColorCalculator::isLit(const glm::vec4& point, Light* light) const {
    vec4 l;
    if (light->position.w == 0) {
        l = light->position;
    } else {
        l = vec4(glm::normalize(vec3(light->position - point)), 0);
    }
    Ray* ray = new Ray();
    ray->pos = point + (l * 0.001f);
    ray->dir = l;

    Intersection* lightIntersection = intersectionDetector->getIntersection(ray);
    if (light->position.w == 1) {
        float distToLight = glm::length(vec3(light->position - point));
        const float distToIntersection = lightIntersection->dist;
        if (distToIntersection != 0 && distToIntersection < distToLight) {
            return false;
        }
    }
    return true;
}

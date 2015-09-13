#include "ColorCalculator.h"
#include "Intersection.h"


#include "glm/glm.hpp"
#include "Scene.h"
#include "Ray.h"
#include "Light.h"
#include "Object.h"
#include "Camera.h"

unsigned ColorCalculator::calculate(const Intersection* intersection) const
{
    if (intersection->dist <= 0) {
        return 0;
    }

    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;

    vec4 finalcolor;
    Object* obj = intersection->object;

    for (auto it = scene->lights.begin(); it != scene->lights.end(); it++) {
        Light* light = *it;

        vec4 intersectionPoint = intersection->ray->pos + (intersection->ray->dir * intersection->dist);
        vec3 l = glm::normalize(vec3(light->position - intersectionPoint));

        vec3 normal = obj->getNormal(intersectionPoint);
        float intens = glm::dot(normal, l);
        if (intens < 0) {
            intens = 0;
        }

        const vec4& ambColor = convertToVec(obj->ambient);
        const vec4 ambC = ambColor * intens;
        finalcolor += ambC;
    }
    float chanels[3] = {finalcolor.r, finalcolor.g, finalcolor.b};
    return convertToInt(chanels);
}

unsigned ColorCalculator::convertToInt(float chanels[3]) const {
    unsigned char mask = 0xFF;
    unsigned char r = (unsigned char) (chanels[0] * mask);
    unsigned char g = (unsigned char) (chanels[1] * mask);
    unsigned char b = (unsigned char) (chanels[2] * mask);
    unsigned color(b);
    color |= r << 16;
    color |= g << 8;
    return color;
}

glm::vec4 ColorCalculator::convertToVec(float chanels[3]) const {
    return glm::vec4(chanels[0], chanels[1], chanels[2], 1);
}

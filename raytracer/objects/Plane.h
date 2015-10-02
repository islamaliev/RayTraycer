#pragma once


#include "Object.h"

class Plane : public Object {
public:
    Plane(const glm::vec3& pos, const glm::vec3& norm, float w, float h, float rotation)
        : position(pos, 1)
        , normal(norm)
        , w(w)
        , h(h)
        , rotation(rotation) {}

    double intersect(const Ray* ray) const override;

    glm::vec3 getNormal(const glm::vec4& point) const override;

    glm::vec4 position;
    glm::vec3 normal;
    float w;
    float h;
    float rotation;
};

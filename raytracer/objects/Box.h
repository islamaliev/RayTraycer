#pragma once


#include "Object.h"

class Box : public Object {
public:
    Box(const glm::vec3& pos, float size)
        : position(pos, 1)
        , size(size)
    {}

    double intersect(const Ray* ray) const override;

    glm::vec3 getNormal(const glm::vec4& point) const override;

    glm::vec4 position;
    float size;
};

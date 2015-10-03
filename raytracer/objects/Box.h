#pragma once


#include "Object.h"

class Box : public Object {
public:
    Box(const glm::mat4& m, const glm::vec3& pos, float size);

    double intersect(const Ray* ray) const override;

    glm::vec3 getNormal(const glm::vec4& point) const override;

    glm::vec4 position;
    float size;
};

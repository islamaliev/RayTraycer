#pragma once


#include "Object.h"

class Sphere : public Object {
public:
    Sphere(const glm::mat4& m, const glm::vec3& pos, float radius);

    double intersect(const Ray* ray) const override;

    glm::vec3 getNormal(const glm::vec4& point) const override;

    glm::vec4 position;
    float radius;
};

#pragma once


#include "Object.h"

class Plane : public Object {
public:
    static const glm::vec3 DEFAULT_NORMAL;

    Plane(const mat4& m, const glm::vec3& pos, const glm::vec3& norm, float w, float h, float rotation);

    double intersect(const Ray* ray) const override;

    glm::vec3 getNormal(const glm::vec4& point) const override;

    glm::vec4 position;
    glm::vec4 localNormal;
    float w;
    float h;
    float rotation;
    glm::vec3 normal;

private:
    bool isPointInBounds(const glm::vec4& p) const;
};

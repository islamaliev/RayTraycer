#pragma once


#include "Object.h"

class Triangle : public Object {
public:
    Triangle(const glm::mat4& m, const vec3* v1, const vec3* v2, const vec3* v3);

    double intersect(const Ray* ray) const override;

    glm::vec3 getNormal(const glm::vec4& point) const override;

    std::vector<const vec3*> verticies;

private:
    bool isPointInTriangle(const vec3& p, const vec3& a, const vec3& b, const vec3& c) const;

    vec4 localNormal;
    vec3 normal;
};
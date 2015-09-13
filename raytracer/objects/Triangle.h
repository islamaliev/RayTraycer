#pragma once


#include <vector>
#include "Object.h"
#include "glm/glm.hpp"
#include "Camera.h"


class Triangle : public Object {
public:
    Triangle(const vec3* v1, const vec3* v2, const vec3* v3);

    float intersect(const Ray* ray) const override;

    glm::vec3 getNormal(glm::vec4 point) override;

    std::vector<const vec3*> verticies;

private:
    bool isPointInTriangle(const vec3& p, const vec3& a, const vec3& b, const vec3& c) const;
};
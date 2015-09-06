#pragma once


#include <vector>
#include "Object.h"
#include "glm/glm.hpp"
#include "Camera.h"


class Triangle : public Object {
public:
    Triangle(const vec3* v1, const vec3* v2, const vec3* v3);

    float intersect(Ray* ray) override;

    std::vector<const vec3*> verticies;

private:
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
    typedef glm::mat4 mat4;

    bool isPointInTriangle(const vec3& p, const vec3& a, const vec3& b, const vec3& c);
};
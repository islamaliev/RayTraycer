#ifndef HW3_SPHERE_H
#define HW3_SPHERE_H


#include "Object.h"
#include "glm/glm.hpp"

class Sphere : public Object {
public:
    Sphere(glm::vec3 pos, float radius)
        : position(pos, 1)
        , radius(radius)
    {}

    double intersect(const Ray* ray) const override;

    glm::vec3 getNormal(const glm::vec4& point) const override;

    glm::vec4 position;
    float radius;
};


#endif //HW3_SPHERE_H

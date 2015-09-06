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


    float intersect(Ray* ray) override;

    glm::vec4 position;
    float radius;
};


#endif //HW3_SPHERE_H

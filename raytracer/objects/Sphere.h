#ifndef HW3_SPHERE_H
#define HW3_SPHERE_H


#include "Object.h"
#include "glm/glm.hpp"

class Sphere : public Object {
public:
    Sphere(glm::vec3 pos, float radius)
        : position(pos)
        , radius(radius)
    {}


    float intersect(Ray* ray) override;

    glm::vec3 position;
    float radius;
};


#endif //HW3_SPHERE_H

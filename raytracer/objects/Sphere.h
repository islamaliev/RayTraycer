#ifndef HW3_SPHERE_H
#define HW3_SPHERE_H


#include "Object.h"

class Sphere : public Object {
public:
    float intersect(Ray* ray) override;

    float radius;
};


#endif //HW3_SPHERE_H

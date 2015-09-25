#pragma once

#include "Ray.h"

class Object;

struct Intersection {
    Intersection(double dist, Ray* ray, Object* object): dist(dist), ray(ray), object(object) {
        point = ray->pos + ray->dir * dist;
    };

    ~Intersection() {
        ray = nullptr;
        object = nullptr;
    }
    double dist;
    glm::vec4 point;
    const Object* object;
    const Ray* ray;
};

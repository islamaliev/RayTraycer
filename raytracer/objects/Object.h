#pragma once


#include "glm/glm.hpp"

class Ray;

class Object {
public:
    Object()
        : transform(1.f)
    {}

    virtual float intersect(Ray* ray) { return 0; }

    glm::mat4 transform;

    float ambient[3];
    float diffuse[3];
    float specular[3];
    float emission[3];
    float shininess;
};

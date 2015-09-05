#pragma once


class Ray;

class Object {
public:
    virtual float intersect(Ray* ray) { return 0; }

    float ambient[3];
    float diffuse[3];
    float specular[3];
    float emission[3];
    float shininess;
};
